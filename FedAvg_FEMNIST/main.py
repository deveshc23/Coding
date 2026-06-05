import logging
import random

import torch

logging.basicConfig(level=logging.INFO, format="%(asctime)s [MAIN] %(message)s")
log = logging.getLogger(__name__)

NUM_CLIENTS = 2000
CLIENTS_PER_ROUND = 50
BATCH_SIZE = 64
LOCAL_EPOCHS = 5
ROUNDS = 1000
LR = 0.001

CHECKPOINT_PATH = "fedavg_checkpoint.pt"
EVAL_EVERY = 5


def main():
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    log.info(f"Device: {device}")

    from preprocess import load_and_split

    client_loaders, test_loader, meta = load_and_split(NUM_CLIENTS, BATCH_SIZE)

    from model import get_model

    global_model = get_model(meta["num_classes"])

    from server import FedAvgServer

    server = FedAvgServer(global_model, device)

    from client import FedClient

    clients = [
        FedClient(i, client_loaders[i], device, LR, LOCAL_EPOCHS)
        for i in range(NUM_CLIENTS)
    ]

    log.info("Starting FedAvg training...")

    results = []
    for rnd in range(1, ROUNDS + 1):
        log.info(f"--- Round {rnd}/{ROUNDS} ---")
        selected = random.sample(range(NUM_CLIENTS), CLIENTS_PER_ROUND)
        global_weights = server.get_global_weights()
        updates = []

        for cid in selected:
            state_dict, n = clients[cid].train(global_weights)
            updates.append((state_dict, n))

        server.aggregate(updates)

        if rnd % EVAL_EVERY == 0 or rnd == ROUNDS:
            metrics = server.evaluate(test_loader)
            results.append({"round": rnd, **metrics})

            log.info(
                f"Round {rnd} | loss={metrics['loss']:.4f} | acc={metrics['accuracy']:.4f}"
            )
            # save checkpoint after every evaluation
            server.save_checkpoint(CHECKPOINT_PATH)

    log.info("Training complete.")

    # visualize directly from in-memory results — no JSON file needed
    from visualize import plot_all

    plot_all(results)
    log.info("Plots generated successfully.")


if __name__ == "__main__":
    main()
