import json
import logging
import os
import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

logging.basicConfig(level=logging.INFO, format="%(asctime)s [VIZ] %(message)s")
log = logging.getLogger(__name__)

# fix: use /tmp as default so it is always writable on clusters where the
# working directory may be read-only. Override by setting the PLOT_DIR env var:
#   export PLOT_DIR=/home/user/my_plots
OUTPUT_DIR = os.environ.get("PLOT_DIR", "/tmp/fl_plots")


def load_results(path):
    if not os.path.exists(path):
        raise FileNotFoundError(f"{path} not found.")
    with open(path, "r") as f:
        return json.load(f)


def plot_all(results, output_dir=OUTPUT_DIR):
    os.makedirs(output_dir, exist_ok=True)

    rounds   = [r["round"]    for r in results]
    loss     = [r["loss"]     for r in results]
    accuracy = [r["accuracy"] for r in results]
    acc_pct  = [a * 100 for a in accuracy]

    # ── Figure 1: 2×2 summary grid (fix: removed perplexity subplot entirely) ──
    fig = plt.figure(figsize=(14, 9))
    fig.suptitle(
        "Federated Learning — FedAvg on FEMNIST",
        fontsize=15, fontweight="bold", y=0.98
    )
    gs = gridspec.GridSpec(2, 2, figure=fig, hspace=0.42, wspace=0.32)

    # subplot 1 — accuracy curve
    ax1 = fig.add_subplot(gs[0, 0])
    ax1.plot(rounds, acc_pct, marker="o", color="#2563EB", linewidth=2, markersize=5)
    ax1.fill_between(rounds, acc_pct, alpha=0.12, color="#2563EB")
    ax1.set_title("Accuracy per Round", fontweight="bold")
    ax1.set_xlabel("Round")
    ax1.set_ylabel("Accuracy (%)")
    ax1.set_ylim(0, 100)
    ax1.grid(True, linestyle="--", alpha=0.5)
    for x, y in zip(rounds, acc_pct):
        ax1.annotate(
            f"{y:.1f}%", (x, y),
            textcoords="offset points", xytext=(0, 7),
            ha="center", fontsize=7.5
        )

    # subplot 2 — loss curve
    ax2 = fig.add_subplot(gs[0, 1])
    ax2.plot(rounds, loss, marker="s", color="#DC2626", linewidth=2, markersize=5)
    ax2.fill_between(rounds, loss, alpha=0.12, color="#DC2626")
    ax2.set_title("Cross-Entropy Loss per Round", fontweight="bold")
    ax2.set_xlabel("Round")
    ax2.set_ylabel("Loss")
    ax2.grid(True, linestyle="--", alpha=0.5)

    # subplot 3 — accuracy vs loss dual-axis (replaces the perplexity plot)
    ax3 = fig.add_subplot(gs[1, 0])
    ax3.plot(rounds, acc_pct, marker="o", color="#2563EB", linewidth=2, markersize=5)
    ax3.set_xlabel("Round")
    ax3.set_ylabel("Accuracy (%)", color="#2563EB")
    ax3.tick_params(axis="y", labelcolor="#2563EB")
    ax3b = ax3.twinx()
    ax3b.plot(rounds, loss, marker="s", color="#DC2626", linewidth=2,
              markersize=5, linestyle="--")
    ax3b.set_ylabel("Loss", color="#DC2626")
    ax3b.tick_params(axis="y", labelcolor="#DC2626")
    ax3.set_title("Accuracy vs Loss (dual axis)", fontweight="bold")
    ax3.grid(True, linestyle="--", alpha=0.4)

    # subplot 4 — fix: bar chart now shows only the two compatible metrics
    # (accuracy % and loss) on separate grouped bars with twin axes to avoid
    # mixing incompatible scales on a single Y-axis
    final = results[-1]
    ax4 = fig.add_subplot(gs[1, 1])
    metrics = ["Accuracy (%)", "Loss"]
    values  = [final["accuracy"] * 100, final["loss"]]
    colors  = ["#2563EB", "#DC2626"]
    bars = ax4.bar(metrics, values, color=colors, alpha=0.82, width=0.45)
    ax4.set_title(f"Final Metrics (Round {final['round']})", fontweight="bold")
    ax4.set_ylabel("Value")
    ax4.grid(True, axis="y", linestyle="--", alpha=0.5)
    for bar, val in zip(bars, values):
        ax4.text(
            bar.get_x() + bar.get_width() / 2,
            bar.get_height() + 0.3,
            f"{val:.2f}",
            ha="center", fontsize=9, fontweight="bold"
        )

    out1 = os.path.join(output_dir, "fl_training_summary.png")
    plt.savefig(out1, dpi=150, bbox_inches="tight")
    log.info(f"Summary plot saved → {out1}")
    plt.close()

    # ── Figure 2: standalone accuracy vs loss dual-axis ──
    fig2, ax = plt.subplots(figsize=(9, 5))
    ax.plot(rounds, acc_pct, marker="o", color="#2563EB",
            linewidth=2.5, markersize=6, label="Accuracy")
    ax2b = ax.twinx()
    ax2b.plot(rounds, loss, marker="s", color="#DC2626",
              linewidth=2.5, markersize=6, linestyle="--", label="Loss")
    ax.set_xlabel("Communication Round", fontsize=11)
    ax.set_ylabel("Accuracy (%)", color="#2563EB", fontsize=11)
    ax2b.set_ylabel("Loss", color="#DC2626", fontsize=11)
    ax.set_ylim(0, 100)
    ax.set_title("Accuracy vs Loss — FedAvg (FEMNIST)", fontsize=13, fontweight="bold")
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

    log.info(f"All plots saved to: {output_dir}")


# standalone use: python visualize.py <path_to_results.json>
# primary use: called directly from main.py with in-memory results (no file needed)
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python visualize.py <path_to_results.json>")
        print("       (Or run main.py which calls plot_all() directly in memory)")
        sys.exit(1)
    results = load_results(sys.argv[1])
    plot_all(results)
