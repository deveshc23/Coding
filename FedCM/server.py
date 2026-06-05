import copy
import logging
import torch
import torch.nn as nn
import torch.nn.functional as F

logging.basicConfig(level=logging.INFO, format="%(asctime)s [SERVER] %(message)s")
log = logging.getLogger(__name__)

# Keys in state_dict belonging to the personalized classification head.
# These are NEVER averaged — the whole point of FedCM.
PERSONAL_KEYS = {"fc2.weight", "fc2.bias"}


class FedCMServer:
    def __init__(self, base_model, device, num_clients, migration_threshold=0.5):
        self.base_model = base_model.to(device)
        self.device = device
        self.criterion = nn.CrossEntropyLoss()
        self.round = 0
        self.num_clients = num_clients
        self.migration_threshold = migration_threshold  # ✅ FIX: was 0.8, now 0.5

        self.client_clusters = {i: -1 for i in range(num_clients)}
        self.cluster_models = {}
        # ✅ FIX: Store LIST of per-round delta_w tensors (not concatenated)
        self.client_gradient_paths = {i: [] for i in range(num_clients)}
        self.client_personal_weights = {i: None for i in range(num_clients)}
        # Cooldown to prevent excessive migration
        self.client_migration_cooldown = {i: 0 for i in range(num_clients)}

    def get_client_weights(self, client_id):
        cluster_id = self.client_clusters[client_id]
        if cluster_id == -1:
            state = {
                k: v.cpu().clone() for k, v in self.base_model.state_dict().items()
            }
        else:
            state = {
                k: v.cpu().clone()
                for k, v in self.cluster_models[cluster_id].state_dict().items()
            }

        if self.client_personal_weights[client_id] is not None:
            for key, val in self.client_personal_weights[client_id].items():
                state[key] = val.clone()

        return {"state_dict": state}

    def store_warmup_gradients(self, client_id, delta_w):
        # Store per-round tensors — needed for paper's Eq.4
        self.client_gradient_paths[client_id].append(delta_w.cpu())

    def warmup_aggregate(self, updates):
        """
        FedAvg on BACKBONE ONLY during warm-up.
        ✅ FIX: fc2 (PERSONAL_KEYS) is explicitly excluded from averaging.
        """
        if not updates:
            return
        total_samples = sum(n for _, n in updates)
        new_state = copy.deepcopy(self.base_model.state_dict())

        # ✅ FIX: Zero only backbone keys, not fc2
        for key in new_state:
            if key not in PERSONAL_KEYS:
                new_state[key] = torch.zeros_like(new_state[key], dtype=torch.float32)

        for state_dict, n in updates:
            weight = n / total_samples
            for key in new_state:
                if key not in PERSONAL_KEYS:  # ✅ FIX: skip fc2!
                    new_state[key] += state_dict[key].float() * weight

        self.base_model.load_state_dict(new_state)
        log.info("Warmup: Backbone (conv1/conv2/fc1) updated. fc2 untouched.")

    def persist_warmup_personal_weights(self, last_warmup_state):
        """Preserve each warmup client's personal fc2 learned during warmup."""
        for cid, state_dict in last_warmup_state.items():
            self.client_personal_weights[cid] = {
                key: val.cpu().clone()
                for key, val in state_dict.items()
                if key in PERSONAL_KEYS
            }
        log.info(f"Persisted personal fc2 for {len(last_warmup_state)} clients.")

    def _compute_similarity_matrix(self, active_clients):
        """
        ✅ FIX: Implement paper's Eq.4 exactly.
        s_ij = Σ_t <g_i^(t), g_j^(t)>  /  (Σ_t ||g_i^(t)||  *  Σ_t ||g_j^(t)||)

        This is NOT standard cosine similarity on the concatenated vector.
        The denominator is a product of SUMMED norms (per-round), not the
        norm of the concatenated path vector.
        """
        N = len(active_clients)
        sim_matrix = torch.zeros(N, N)

        for i in range(N):
            for j in range(i, N):
                g_i = self.client_gradient_paths[active_clients[i]]
                g_j = self.client_gradient_paths[active_clients[j]]

                if not g_i or not g_j:
                    continue

                T = min(len(g_i), len(g_j))

                # Numerator: sum of per-round dot products
                dot_sum = sum(
                    torch.dot(g_i[t].flatten(), g_j[t].flatten()).item()
                    for t in range(T)
                )
                # Denominator: product of summed per-round norms
                norm_sum_i = sum(torch.norm(g_i[t]).item() for t in range(T))
                norm_sum_j = sum(torch.norm(g_j[t]).item() for t in range(T))

                s_ij = dot_sum / (norm_sum_i * norm_sum_j + 1e-9)
                # ✅ FIX: Clip negatives — modularity requires non-negative weights
                s_ij = max(s_ij, 0.0)

                sim_matrix[i, j] = s_ij
                sim_matrix[j, i] = s_ij

        # ✅ FIX: Remove self-loops (diagonal = 0) for correct modularity
        sim_matrix.fill_diagonal_(0.0)
        return sim_matrix

    def discover_clusters(self, active_clients):
        log.info("Executing Fed-CM Adaptive Cluster Discovery...")
        N = len(active_clients)
        client_idx_map = {idx: c for idx, c in enumerate(active_clients)}

        # ✅ FIX: Use paper's Eq.4 similarity formula
        sim_matrix = self._compute_similarity_matrix(active_clients)

        m = sim_matrix.sum().item() / 2.0
        if m < 1e-9:
            log.warning("Near-zero total similarity — using single cluster.")
            self.cluster_models = {0: copy.deepcopy(self.base_model)}
            for c in active_clients:
                self.client_clusters[c] = 0
            return

        # Modularity-based clustering (Algorithm 1 from paper)
        clusters = {i: [i] for i in range(N)}
        node_cluster = {i: i for i in range(N)}

        def compute_modularity(clusters_dict):
            q = 0.0
            for c_nodes in clusters_dict.values():
                if not c_nodes:
                    continue
                c_tensor = torch.tensor(c_nodes, dtype=torch.long)
                in_weight = sim_matrix[c_tensor][:, c_tensor].sum().item()
                tot_weight = sim_matrix[c_tensor].sum().item()
                q += (in_weight / (2 * m)) - ((tot_weight / (2 * m)) ** 2)
            return q

        changed = True
        while changed:
            changed = False
            for i in range(N):
                current_c = node_cluster[i]
                best_c = current_c
                best_q_increase = 0.0
                base_q = compute_modularity(clusters)
                unique_clusters = list(set(node_cluster.values()))

                for target_c in unique_clusters:
                    if target_c == current_c:
                        continue
                    clusters[current_c].remove(i)
                    clusters[target_c].append(i)
                    new_q = compute_modularity(clusters)
                    delta_q = new_q - base_q
                    if delta_q > best_q_increase:
                        best_q_increase = delta_q
                        best_c = target_c
                    clusters[target_c].remove(i)
                    clusters[current_c].append(i)

                if best_c != current_c:
                    clusters[current_c].remove(i)
                    clusters[best_c].append(i)
                    node_cluster[i] = best_c
                    changed = True

        unique_final = list(set(node_cluster.values()))
        self.cluster_models = {}
        for real_cluster_iṭd, internal_c_id in enumerate(unique_final):
            self.cluster_models[real_cluster_id] = copy.deepcopy(self.base_model)
            for node_idx in clusters[internal_c_id]:
                real_client_id = client_idx_map[node_idx]
                self.client_clusters[real_client_id] = real_cluster_id

        log.info(f"Discovered {len(unique_final)} clusters among {N} active clients.")

    def assign_new_client_to_cluster(self, client_id):
        if self.client_clusters[client_id] != -1:
            return
        if len(self.cluster_models) == 0:
            return
        cluster_loads = {c: 0 for c in self.cluster_models.keys()}
        for cid in range(self.num_clients):
            c_id = self.client_clusters[cid]
            if c_id != -1:
                cluster_loads[c_id] += 1
        best_cluster = min(self.cluster_models.keys(), key=lambda c: cluster_loads[c])
        self.client_clusters[client_id] = best_cluster
        log.info(
            f"Assigned Client {client_id} → Cluster {best_cluster} (load balancing)"
        )

    def store_training_gradients(self, client_id, delta_w):
        if len(self.client_gradient_paths[client_id]) < 15:
            self.client_gradient_paths[client_id].append(delta_w.cpu())
        else:
            self.client_gradient_paths[client_id] = self.client_gradient_paths[
                client_id
            ][1:] + [delta_w.cpu()]

    def aggregate_and_migrate(self, client_updates, store_gradients=True):
        """
        Fed-CM Aggregation with fixes:
        1. Persist personal fc2 per client
        2. Compute cluster average direction (magnitude-weighted, paper Eq.7)
        3. Leave-one-out migration check to avoid trivial self-similarity
        4. FedAvg ONLY backbone keys
        5. Decrement migration cooldowns
        """
        # ── Step 1: Persist personal fc2 ─────────────────────────────────────
        for cid, state_dict, n, delta_w in client_updates:
            self.client_personal_weights[cid] = {
                key: val.cpu().clone()
                for key, val in state_dict.items()
                if key in PERSONAL_KEYS
            }

        # ── Step 2: Compute per-cluster weighted update direction ─────────────
        # All on device for consistency
        cluster_angle_accum = {c: None for c in self.cluster_models.keys()}
        cluster_angle_count = {c: 0 for c in self.cluster_models.keys()}
        client_angles = {}

        for cid, state_dict, n, delta_w in client_updates:
            c_id = self.client_clusters[cid]
            if c_id not in cluster_angle_accum:
                continue
            # ✅ FIX: ensure everything on self.device
            delta_w_dev = delta_w.to(self.device)
            norm_w = torch.norm(delta_w_dev, p=2)
            theta_i = delta_w_dev / (norm_w + 1e-9)
            client_angles[cid] = theta_i

            contrib = norm_w * theta_i
            if cluster_angle_accum[c_id] is None:
                cluster_angle_accum[c_id] = contrib.clone()
            else:
                cluster_angle_accum[c_id] = cluster_angle_accum[c_id] + contrib
            cluster_angle_count[c_id] += 1

        # Normalize cluster accumulators to unit vectors
        global_angles = {}
        for c, accum in cluster_angle_accum.items():
            if accum is not None:
                global_angles[c] = accum / (torch.norm(accum, p=2) + 1e-9)

        # ── Step 3: Migration with leave-one-out ──────────────────────────────
        for cid, state_dict, n, delta_w in client_updates:
            c_id = self.client_clusters[cid]
            if c_id not in global_angles or cid not in client_angles:
                continue

            # ✅ FIX: Decrement cooldown
            if self.client_migration_cooldown[cid] > 0:
                self.client_migration_cooldown[cid] -= 1
                continue

            # ✅ FIX: Leave-one-out — subtract this client's contribution
            my_norm = torch.norm(client_angles[cid])
            loo_accum = cluster_angle_accum[c_id] - my_norm * client_angles[cid]
            if cluster_angle_count[c_id] <= 1 or torch.norm(loo_accum) < 1e-9:
                continue  # No reference direction without this client

            loo_angle = loo_accum / (torch.norm(loo_accum) + 1e-9)
            sim = torch.dot(client_angles[cid], loo_angle).item()

            if sim < self.migration_threshold:
                best_c = c_id
                best_sim = sim
                for test_c, g_angle in global_angles.items():
                    test_sim = torch.dot(client_angles[cid], g_angle).item()
                    if test_sim > best_sim:
                        best_sim = test_sim
                        best_c = test_c

                if best_c != c_id:
                    log.info(
                        f"Migrating Client {cid}: Cluster {c_id}→{best_c} "
                        f"(sim {sim:.3f}→{best_sim:.3f})"
                    )
                    self.client_clusters[cid] = best_c
                    # ✅ FIX: cooldown prevents immediate re-migration
                    self.client_migration_cooldown[cid] = 5

        # ── Step 4: Backbone-only FedAvg within each cluster ─────────────────
        cluster_updates = {c: [] for c in self.cluster_models.keys()}
        for cid, state_dict, n, delta_w in client_updates:
            c_id = self.client_clusters[cid]
            if c_id in cluster_updates:
                cluster_updates[c_id].append((state_dict, n))

        for c_id, updates in cluster_updates.items():
            if not updates:
                continue
            total_samples = sum(n for _, n in updates)
            new_state = copy.deepcopy(self.cluster_models[c_id].state_dict())

            for key in new_state:
                if key not in PERSONAL_KEYS:
                    new_state[key] = torch.zeros_like(
                        new_state[key], dtype=torch.float32
                    )

            for state_dict, num_samples in updates:
                weight = num_samples / total_samples
                for key in new_state:
                    if key not in PERSONAL_KEYS:  # ✅ fc2 intentionally excluded
                        new_state[key] += state_dict[key].float() * weight

            self.cluster_models[c_id].load_state_dict(new_state)

        # ── Step 5: Store gradient paths for smarter future migration ─────────
        if store_gradients:
            for cid, state_dict, n, delta_w in client_updates:
                self.store_training_gradients(cid, delta_w)

        self.round += 1
        log.info(
            f"Round {self.round} | Backbone aggregated across "
            f"{len(self.cluster_models)} clusters. Personal fc2 preserved."
        )

    def evaluate(self, test_loader):
        if not self.cluster_models:
            return {"loss": 0.0, "accuracy": 0.0}
        cluster_losses, cluster_accs = [], []
        for c_id, model in self.cluster_models.items():
            model.eval()
            c_loss, c_correct, c_samples = 0.0, 0, 0
            with torch.no_grad():
                for seqs, tgts in test_loader:
                    seqs, tgts = seqs.to(self.device), tgts.to(self.device)
                    logits = model(seqs)
                    loss = self.criterion(logits, tgts)
                    c_loss += loss.item() * tgts.numel()
                    preds = logits.argmax(dim=1)
                    c_correct += (preds == tgts).sum().item()
                    c_samples += tgts.size(0)
            cluster_losses.append(c_loss / max(c_samples, 1))
            cluster_accs.append(c_correct / max(c_samples, 1))
        avg_loss = sum(cluster_losses) / len(cluster_losses)
        avg_acc = sum(cluster_accs) / len(cluster_accs)
        log.info(
            f"Round {self.round} eval | avg_loss={avg_loss:.4f} | "
            f"avg_acc={avg_acc:.4f} | clusters={len(self.cluster_models)}"
        )
        return {"loss": avg_loss, "accuracy": avg_acc}
