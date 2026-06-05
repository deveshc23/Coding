import logging
import random

import torch

logging.basicConfig(level=logging.INFO, format="%(asctime)s [MAIN] %(message)s")
log = logging.getLogger(__name__)

NUM_CLIENTS = 2000
CLIENTS_PER_ROUND = 500
BATCH_SIZE = 64
LOCAL_EPOCHS = 5
WARMUP_ROUNDS = 3
ROUNDS = 1000
LR = 0.001
# ✅ FIX: Reduced from 0.8 to 0.5 — prevents excessive migration churn
MIGRATION_THRESHOLD = 0.6
EVAL_EVERY = 5


def main():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    log.info(f"Device: {device}")

    from preprocess import load_and_split

    client_loaders, test_loader, meta = load_and_split(NUM_CLIENTS, BATCH_SIZE)

    from model import get_model

    base_model = get_model(meta["num_classes"])
    client_runner_model = get_model(meta["num_classes"]).to(device)

    from server import FedCMServer

    server = FedCMServer(base_model, device, NUM_CLIENTS, MIGRATION_THRESHOLD)

    from client import FedClient

    clients = [
        FedClient(i, client_loaders[i], device, LR, LOCAL_EPOCHS)
        for i in range(NUM_CLIENTS)
    ]

    results = []

    # ==========================================
    # PHASE 1: WARM-UP TRAINING
    # ==========================================
    log.info("Starting Fed-CM Warm-up Phase...")
    # ✅ FIX: Use a FIXED set of warmup clients across all warmup rounds
    # so gradient paths are accumulated for the same clients.
    # Using a different random subset each round means many clients have
    # fewer than WARMUP_ROUNDS entries in their gradient_paths list.
    warmup_clients = random.sample(range(NUM_CLIENTS), CLIENTS_PER_ROUND)
    last_warmup_state = {}

    for rnd in range(1, WARMUP_ROUNDS + 1):
        log.info(f"--- Warmup Round {rnd}/{WARMUP_ROUNDS} ---")
        warmup_updates = []
        last_warmup_state = {}

        for cid in warmup_clients:
            weights = server.get_client_weights(cid)
            state_dict, n, delta_w = clients[cid].train(client_runner_model, weights)
            server.store_warmup_gradients(cid, delta_w)
            warmup_updates.append((state_dict, n))
            last_warmup_state[cid] = state_dict

        # ✅ Backbone-only FedAvg (fc2 excluded — fixed in server.warmup_aggregate)
        server.warmup_aggregate(warmup_updates)

    # Preserve each warmup client's personal fc2 from their last training round
    server.persist_warmup_personal_weights(last_warmup_state)

    # ==========================================
    # PHASE 2: CLUSTER DISCOVERY
    # ==========================================
    # ✅ FIX: Pass warmup_clients (fixed set) — all have T=WARMUP_ROUNDS entries
    server.discover_clusters(warmup_clients)

    # ==========================================
    # PHASE 3: CLUSTERED FL & MIGRATION
    # ==========================================
    log.info("Starting Fed-CM Clustered Training...")

    for rnd in range(1, ROUNDS + 1):
        log.info(f"--- Round {rnd}/{ROUNDS} ---")
        selected = random.sample(range(NUM_CLIENTS), CLIENTS_PER_ROUND)
        updates = []

        for cid in selected:
            if server.client_clusters[cid] == -1 and len(server.cluster_models) > 0:
                server.assign_new_client_to_cluster(cid)

            weights = server.get_client_weights(cid)
            state_dict, n, delta_w = clients[cid].train(client_runner_model, weights)
            updates.append((cid, state_dict, n, delta_w))

        server.aggregate_and_migrate(updates, store_gradients=True)

        if rnd % EVAL_EVERY == 0 or rnd == ROUNDS:
            metrics = server.evaluate(test_loader)
            results.append({"round": rnd, **metrics})

    log.info("Training complete.")

    from visualize import plot_all

    plot_all(results)
    log.info("Plots generated successfully.")


if __name__ == "__main__":
    main()
