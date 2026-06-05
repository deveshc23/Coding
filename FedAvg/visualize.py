import json
import logging
import os
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

logging.basicConfig(level=logging.INFO, format="%(asctime)s [VIZ] %(message)s")
log = logging.getLogger(__name__)

RESULTS_PATH = "fl_results.json"
OUTPUT_DIR = "plots"

def load_results(path=RESULTS_PATH):
    if not os.path.exists(path):
        raise FileNotFoundError(f"{path} not found. Run main.py first.")
    with open(path, "r") as f:
        return json.load(f)

def plot_all(results, output_dir=OUTPUT_DIR):
    os.makedirs(output_dir, exist_ok=True)
    rounds = [r["round"] for r in results]
    loss = [r["loss"] for r in results]
    accuracy = [r["accuracy"] for r in results]
    perplexity = [r["perplexity"] for r in results]
    acc_pct = [a * 100 for a in accuracy]

    fig = plt.figure(figsize=(16, 10))
    fig.suptitle("Federated Learning — FedAvg on Shakespeare", fontsize=15, fontweight="bold", y=0.98)
    gs = gridspec.GridSpec(2, 2, figure=fig, hspace=0.42, wspace=0.32)

    ax1 = fig.add_subplot(gs[0, 0])
    ax1.plot(rounds, acc_pct, marker="o", color="#2563EB", linewidth=2, markersize=5)
    ax1.fill_between(rounds, acc_pct, alpha=0.12, color="#2563EB")
    ax1.set_title("Accuracy per Round", fontweight="bold")
    ax1.set_xlabel("Round")
    ax1.set_ylabel("Accuracy (%)")
    ax1.set_ylim(0, 100)
    ax1.grid(True, linestyle="--", alpha=0.5)
    for x, y in zip(rounds, acc_pct):
        ax1.annotate(f"{y:.1f}%", (x, y), textcoords="offset points", xytext=(0, 7), ha="center", fontsize=7.5)

    ax2 = fig.add_subplot(gs[0, 1])
    ax2.plot(rounds, loss, marker="s", color="#DC2626", linewidth=2, markersize=5)
    ax2.fill_between(rounds, loss, alpha=0.12, color="#DC2626")
    ax2.set_title("Cross-Entropy Loss per Round", fontweight="bold")
    ax2.set_xlabel("Round")
    ax2.set_ylabel("Loss")
    ax2.grid(True, linestyle="--", alpha=0.5)

    ax3 = fig.add_subplot(gs[1, 0])
    ax3.plot(rounds, perplexity, marker="^", color="#7C3AED", linewidth=2, markersize=5)
    ax3.fill_between(rounds, perplexity, alpha=0.12, color="#7C3AED")
    ax3.set_title("Perplexity per Round", fontweight="bold")
    ax3.set_xlabel("Round")
    ax3.set_ylabel("Perplexity")
    ax3.grid(True, linestyle="--", alpha=0.5)

    ax4 = fig.add_subplot(gs[1, 1])
    bar_colors = ["#2563EB", "#DC2626", "#7C3AED"]
    final = results[-1]
    metrics = ["Accuracy (%)", "Loss", "Perplexity"]
    values = [final["accuracy"] * 100, final["loss"], final["perplexity"]]
    bars = ax4.bar(metrics, values, color=bar_colors, alpha=0.82, width=0.45)
    ax4.set_title(f"Final Metrics (Round {final['round']})", fontweight="bold")
    ax4.set_ylabel("Value")
    ax4.grid(True, axis="y", linestyle="--", alpha=0.5)
    for bar, val in zip(bars, values):
        ax4.text(bar.get_x() + bar.get_width() / 2, bar.get_height() + 0.3, f"{val:.2f}", ha="center", fontsize=9, fontweight="bold")

    out_path = os.path.join(output_dir, "fl_training_summary.png")
    plt.savefig(out_path, dpi=150, bbox_inches="tight")
    log.info(f"Summary plot saved → {out_path}")
    plt.close()

    fig2, ax = plt.subplots(figsize=(9, 5))
    ax.plot(rounds, acc_pct, marker="o", color="#2563EB", linewidth=2.5, markersize=6, label="Accuracy")
    ax2b = ax.twinx()
    ax2b.plot(rounds, loss, marker="s", color="#DC2626", linewidth=2.5, markersize=6, linestyle="--", label="Loss")
    ax.set_xlabel("Communication Round", fontsize=11)
    ax.set_ylabel("Accuracy (%)", color="#2563EB", fontsize=11)
    ax2b.set_ylabel("Loss", color="#DC2626", fontsize=11)
    ax.set_ylim(0, 100)
    ax.set_title("Accuracy vs Loss — FedAvg (Shakespeare)", fontsize=13, fontweight="bold")
    ax.tick_params(axis="y", labelcolor="#2563EB")
    ax2b.tick_params(axis="y", labelcolor="#DC2626")
    lines1, labels1 = ax.get_legend_handles_labels()
    lines2, labels2 = ax2b.get_legend_handles_labels()
    ax.legend(lines1 + lines2, labels1 + labels2, loc="lower right", fontsize=10)
    ax.grid(True, linestyle="--", alpha=0.4)
    out2 = os.path.join(output_dir, "accuracy_vs_loss.png")
    fig2.savefig(out2, dpi=150, bbox_inches="tight")
    log.info(f"Accuracy vs Loss plot saved → {out2}")
    plt.close()
    log.info("All plots generated.")

if __name__ == "__main__":
    results = load_results()
    plot_all(results)
