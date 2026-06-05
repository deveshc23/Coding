import os
import json
import logging
import numpy as np
import torch
from torch.utils.data import Dataset, DataLoader

logging.basicConfig(level=logging.INFO, format="%(asctime)s [PREPROCESS] %(message)s")
log = logging.getLogger(__name__)

SEQ_LEN = 80
TRAIN_SPLIT = 0.9

class CharDataset(Dataset):
    def __init__(self, sequences, targets):
        self.sequences = torch.tensor(sequences, dtype=torch.long)
        self.targets = torch.tensor(targets, dtype=torch.long)
    def __len__(self):
        return len(self.sequences)
    def __getitem__(self, idx):
        return self.sequences[idx], self.targets[idx]

def build_vocab(text):
    chars = sorted(set(text))
    char2idx = {c: i for i, c in enumerate(chars)}
    idx2char = {i: c for c, i in char2idx.items()}
    return char2idx, idx2char, len(chars)

def text_to_sequences(encoded, seq_len):
    seqs, tgts = [], []
    for i in range(0, len(encoded) - seq_len, seq_len):
        seqs.append(encoded[i:i+seq_len])
        tgts.append(encoded[i+1:i+seq_len+1])
    return np.array(seqs), np.array(tgts)

def load_and_split(data_path, num_clients, batch_size):
    if not os.path.exists(data_path):
        raise FileNotFoundError(f"{data_path} not found. Place shakespeare.txt in project root.")
    with open(data_path, "r", encoding="utf-8") as f:
        text = f.read()
    log.info(f"Loaded {len(text):,} characters from {data_path}")
    char2idx, idx2char, vocab_size = build_vocab(text)
    log.info(f"Vocabulary size: {vocab_size}")
    encoded = np.array([char2idx[c] for c in text], dtype=np.int32)
    split_idx = int(len(encoded) * TRAIN_SPLIT)
    train_enc, test_enc = encoded[:split_idx], encoded[split_idx:]
    train_seqs, train_tgts = text_to_sequences(train_enc, SEQ_LEN)
    test_seqs, test_tgts = text_to_sequences(test_enc, SEQ_LEN)
    log.info(f"Train sequences: {len(train_seqs)} | Test sequences: {len(test_seqs)}")
    total = len(train_seqs)
    chunk = total // num_clients
    client_loaders = []
    for i in range(num_clients):
        start = i * chunk
        end = start + chunk if i < num_clients - 1 else total
        ds = CharDataset(train_seqs[start:end], train_tgts[start:end])
        loader = DataLoader(ds, batch_size=batch_size, shuffle=True, drop_last=True)
        client_loaders.append(loader)
        log.info(f"Client {i}: {end - start} sequences, {len(loader)} batches")
    test_ds = CharDataset(test_seqs, test_tgts)
    test_loader = DataLoader(test_ds, batch_size=batch_size, shuffle=False, drop_last=False)
    meta = {"vocab_size": vocab_size, "seq_len": SEQ_LEN, "char2idx": char2idx, "idx2char": {str(k): v for k, v in idx2char.items()}}
    log.info("Preprocessing complete.")
    return client_loaders, test_loader, meta
