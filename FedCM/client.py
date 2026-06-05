import copy
import logging
import torch
import torch.nn as nn

logging.basicConfig(level=logging.INFO, format="%(asctime)s [CLIENT] %(message)s")
log = logging.getLogger(__name__)


class FedClient:
    def __init__(self, client_id, dataloader, device, lr=0.001, local_epochs=2):
        self.client_id = client_id
        self.dataloader = dataloader
        self.device = device
        self.lr = lr
        self.local_epochs = local_epochs
        self.criterion = nn.CrossEntropyLoss()

    def train(self, runner_model, cluster_weights):
        model = runner_model
        model.load_state_dict(cluster_weights["state_dict"])

        # Capture initial fc2 state (before local training this round)
        initial_fc2_w = model.fc2.weight.detach().clone()
        initial_fc2_b = model.fc2.bias.detach().clone()

        optimizer = torch.optim.Adam(model.parameters(), lr=self.lr)
        model.train()
        total_loss = 0.0

        for epoch in range(self.local_epochs):
            epoch_loss = 0.0
            for seqs, tgts in self.dataloader:
                seqs, tgts = seqs.to(self.device), tgts.to(self.device)
                optimizer.zero_grad()
                logits = model(seqs)
                loss = self.criterion(logits, tgts)
                loss.backward()
                nn.utils.clip_grad_norm_(model.parameters(), max_norm=5.0)
                optimizer.step()
                epoch_loss += loss.item()
            total_loss += epoch_loss

        avg_loss = total_loss / (self.local_epochs * max(len(self.dataloader), 1))

        # Δw = w^(t) − w^(t−1) per paper Eq.2 — captures round-level update
        final_fc2_w = model.fc2.weight.detach().clone()
        final_fc2_b = model.fc2.bias.detach().clone()

        delta_w = torch.cat(
            [
                (final_fc2_w - initial_fc2_w).flatten(),
                (final_fc2_b - initial_fc2_b).flatten(),
            ]
        ).cpu()  # ✅ FIX: explicitly on CPU to avoid device mismatch at server

        log.info(
            f"Client {self.client_id} | epochs={self.local_epochs} "
            f"| avg_loss={avg_loss:.4f}"
        )
        return model.state_dict(), len(self.dataloader.dataset), delta_w
