import logging
import torch
import torch.nn as nn

logging.basicConfig(level=logging.INFO, format="%(asctime)s [MODEL] %(message)s")
log = logging.getLogger(__name__)

class CharNN(nn.Module):
    def __init__(self, vocab_size, embed_dim=128, hidden_size=256, dropout=0.3):
        super().__init__()
        self.embed = nn.Embedding(vocab_size, embed_dim)
        self.net = nn.Sequential(
            nn.Linear(embed_dim, hidden_size),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_size, hidden_size),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(hidden_size, vocab_size)
        )
    def forward(self, x, hidden=None):
        x = self.embed(x)
        logits = self.net(x)
        return logits, None

def get_model(vocab_size, embed_dim=128, hidden_size=256, dropout=0.3):
    model = CharNN(vocab_size, embed_dim, hidden_size, dropout)
    total_params = sum(p.numel() for p in model.parameters())
    log.info(f"CharNN | vocab={vocab_size} | embed={embed_dim} | hidden={hidden_size} | layers=3 | params={total_params:,}")
    return model
