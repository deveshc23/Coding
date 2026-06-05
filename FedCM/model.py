import logging

import torch
import torch.nn as nn
import torch.nn.functional as F

logging.basicConfig(level=logging.INFO, format="%(asctime)s [MODEL] %(message)s")
log = logging.getLogger(__name__)


class FEMNISTCNN(nn.Module):
    def __init__(self, num_classes=62):
        super().__init__()
        self.conv1 = nn.Conv2d(1, 32, 3, padding=1)
        self.conv2 = nn.Conv2d(32, 64, 3, padding=1)
        self.pool = nn.MaxPool2d(2)
        self.fc1 = nn.Linear(64 * 7 * 7, 256)

        # This is our personalized layer per the Fed-CM paper
        self.fc2 = nn.Linear(256, num_classes)

    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(x.size(0), -1)
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        return x

    def get_personalized_params(self):
        """Returns the flattened parameters of the classification layer to track gradient paths."""
        return torch.cat(
            [
                self.fc2.weight.detach().clone().flatten(),
                self.fc2.bias.detach().clone().flatten(),
            ]
        )


def get_model(num_classes=62):
    model = FEMNISTCNN(num_classes)
    total_params = sum(p.numel() for p in model.parameters())
    log.info(f"FEMNIST CNN | classes={num_classes} | params={total_params:,}")
    return model
