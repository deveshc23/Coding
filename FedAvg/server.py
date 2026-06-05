import copy
import logging
import math
import torch
import torch.nn as nn

logging.basicConfig(level=logging.INFO, format="%(asctime)s [SERVER] %(message)s")
log = logging.getLogger(__name__)

class FedAvgServer:
    def __init__(self, global_model, device):
        self.global_model = global_model.to(device)
        self.device = device
        self.criterion = nn.CrossEntropyLoss()
        self.round = 0
    def get_global_weights(self):
        return {"model": self.global_model}
    def aggregate(self, client_updates):
        total_samples = sum(n for _, n in client_updates)
        global_state = copy.deepcopy(self.global_model.state_dict())
        for key in global_state:
            global_state[key] = torch.zeros_like(global_state[key], dtype=torch.float32)
        for state_dict, num_samples in client_updates:
            weight = num_samples / total_samples
            for key in global_state:
                global_state[key] += state_dict[key].float() * weight
        self.global_model.load_state_dict(global_state)
        self.round += 1
        log.info(f"Round {self.round} aggregated | {len(client_updates)} clients | {total_samples} total samples")
    def evaluate(self, test_loader):
        self.global_model.eval()
        total_loss = 0.0
        total_correct = 0
        total_tokens = 0
        with torch.no_grad():
            for seqs, tgts in test_loader:
                seqs, tgts = seqs.to(self.device), tgts.to(self.device)
                logits, _ = self.global_model(seqs)
                loss = self.criterion(logits.view(-1, logits.size(-1)), tgts.view(-1))
                total_loss += loss.item() * tgts.numel()
                preds = logits.argmax(dim=-1)
                total_correct += (preds == tgts).sum().item()
                total_tokens += tgts.numel()
        avg_loss = total_loss / total_tokens
        accuracy = total_correct / total_tokens
        perplexity = math.exp(min(avg_loss, 20))
        log.info(f"Round {self.round} eval | loss={avg_loss:.4f} | acc={accuracy:.4f} | ppl={perplexity:.2f}")
        return {"loss": avg_loss, "accuracy": accuracy, "perplexity": perplexity}
    def save_checkpoint(self, path):
        torch.save({"round": self.round, "model_state": self.global_model.state_dict()}, path)
        log.info(f"Checkpoint saved to {path}")
    def load_checkpoint(self, path):
        ckpt = torch.load(path, map_location=self.device)
        self.global_model.load_state_dict(ckpt["model_state"])
        self.round = ckpt["round"]
        log.info(f"Checkpoint loaded from {path} | resuming from round {self.round}")