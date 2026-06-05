import logging
import random
from collections import defaultdict

import numpy as np
import torch
from datasets import load_dataset
from torch.utils.data import DataLoader, Dataset

logging.basicConfig(level=logging.INFO, format="%(asctime)s [PREPROCESS] %(message)s")
log = logging.getLogger(__name__)

TRAIN_SPLIT = 0.7


class FEMNISTDataset(Dataset):
    def __init__(self, images, labels):
        images = np.array(images, dtype=np.float32) / 255.0
        self.images = torch.tensor(images).unsqueeze(1)  # (N,1,28,28)
        self.labels = torch.tensor(labels, dtype=torch.long)

    def __len__(self):
        return len(self.images)

    def __getitem__(self, idx):
        return self.images[idx], self.labels[idx]


def load_and_split(num_clients, batch_size):
    log.info("Loading FEMNIST dataset from HuggingFace cache...")

    dataset = load_dataset(
        "flwrlabs/femnist",
        download_mode="reuse_dataset_if_exists",
        trust_remote_code=True,
    )

    train_ds = dataset["train"]

    # handle missing test split
    if "test" in dataset:
        test_ds = dataset["test"]
    else:
        log.info("Test split not found. Creating test split from train data.")
        split = train_ds.train_test_split(test_size=0.2, seed=42)
        train_ds = split["train"]
        test_ds = split["test"]

    log.info(f"Train samples: {len(train_ds)}")
    log.info(f"Test samples: {len(test_ds)}")

    # group training data by writer_id for natural federated split
    writers = defaultdict(list)

    for sample in train_ds:
        writers[sample["writer_id"]].append(sample)

    writer_ids = list(writers.keys())
    random.shuffle(writer_ids)

    selected_writers = writer_ids[:num_clients]

    client_loaders = []

    for cid, writer in enumerate(selected_writers):
        samples = writers[writer]

        images = [np.array(s["image"]) for s in samples]
        labels = [s["character"] for s in samples]

        split_idx = int(len(images) * TRAIN_SPLIT)

        train_images = images[:split_idx]
        train_labels = labels[:split_idx]

        ds = FEMNISTDataset(train_images, train_labels)

        loader = DataLoader(ds, batch_size=batch_size, shuffle=True, drop_last=True)

        client_loaders.append(loader)

        log.info(f"Client {cid} | writer {writer} | samples {len(train_images)}")

    # create global test loader
    test_images = [np.array(s["image"]) for s in test_ds]
    test_labels = [s["character"] for s in test_ds]

    test_dataset = FEMNISTDataset(test_images, test_labels)

    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

    meta = {"num_classes": 62, "input_shape": (1, 28, 28)}

    log.info("FEMNIST preprocessing complete.")

    return client_loaders, test_loader, meta


def simulate_data_drift(client_loaders, drift_ratio=0.1):
    """
    Simulates data distribution drift by swapping datasets among a percentage of clients.
    Call this from main.py at a specific round (e.g., Round 60) to test Fed-CM's migration strategy.
    """
    num_clients = len(client_loaders)
    num_drift = int(num_clients * drift_ratio)

    if num_drift < 2:
        return client_loaders

    drift_clients = random.sample(range(num_clients), num_drift)
    log.info(f"Simulating Data Drift for {num_drift} clients: {drift_clients}")

    # Shift datasets to the right by 1 among the selected clients
    shifted_loaders = [client_loaders[i] for i in drift_clients]
    shifted_loaders = [shifted_loaders[-1]] + shifted_loaders[:-1]

    for i, cid in enumerate(drift_clients):
        client_loaders[cid] = shifted_loaders[i]

    return client_loaders
