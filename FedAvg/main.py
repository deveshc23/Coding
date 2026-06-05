import json
import logging
import random
import torch
import os

logging.basicConfig(level=logging.INFO, format="%(asctime)s [MAIN] %(message)s")
log = logging.getLogger(__name__)

DATA_PATH = "shakespeare.txt"
NUM_CLIENTS = 20
CLIENTS_PER_ROUND = 10
BATCH_SIZE = 64
LOCAL_EPOCHS = 5
ROUNDS = 200
LR = 0.0005
EMBED_DIM = 256
HIDDEN_SIZE = 512
DROPOUT = 0.3
CHECKPOINT_PATH = "fedavg_checkpoint.pt"
RESULTS_PATH = "fl_results.json"
EVAL_EVERY = 5


def save_and_plot(results):
    path = os.path.join(os.getcwd(), RESULTS_PATH)

    with open(path, "w") as f:
        json.dump(results, f, indent=2)

    log.info(f"Results saved to {path}")

    from visualize import load_results, plot_all
    plot_all(load_results(path))

    log.info("Plots saved to plots/")

def main():
    """Run the FedAvg training loop: train clients, aggregate, evaluate and save results."""
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    log.info(f"Device: {device}")
    log.info(f"Config | clients={NUM_CLIENTS} | per_round={CLIENTS_PER_ROUND} | batch={BATCH_SIZE} | local_epochs={LOCAL_EPOCHS} | rounds={ROUNDS} | lr={LR}")
    from preprocess import load_and_split
    client_loaders, test_loader, meta = load_and_split(DATA_PATH, NUM_CLIENTS, BATCH_SIZE)
    vocab_size = meta["vocab_size"]
    from model import get_model
    global_model = get_model(vocab_size, EMBED_DIM, HIDDEN_SIZE, DROPOUT)
    from server import FedAvgServer
    server = FedAvgServer(global_model, device)
    from client import FedClient
    clients = [FedClient(i, client_loaders[i], device, LR, LOCAL_EPOCHS) for i in range(NUM_CLIENTS)]
    log.info("Starting FedAvg training...")
    results = []
    for rnd in range(1, ROUNDS + 1):
        log.info(f"--- Round {rnd}/{ROUNDS} ---")
        selected = random.sample(range(NUM_CLIENTS), CLIENTS_PER_ROUND)
        log.info(f"Selected clients: {selected}")
        global_weights = server.get_global_weights()
        updates = []
        for cid in selected:
            state_dict, n = clients[cid].train(global_weights)
            updates.append((state_dict, n))
        server.aggregate(updates)
        if rnd % EVAL_EVERY == 0 or rnd == ROUNDS:
            metrics = server.evaluate(test_loader)
            results.append({"round": rnd, **metrics})
            server.save_checkpoint(CHECKPOINT_PATH)
    log.info("Training complete.")
    # save_and_plot(results)
    log.info("Final results:")
    for r in results:
        log.info(f"  Round {r['round']} | loss={r['loss']:.4f} | acc={r['accuracy']:.4f} | ppl={r['perplexity']:.2f}")

if __name__ == "__main__":
    main()

