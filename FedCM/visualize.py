import json
import logging
import os
import sys

import matplotlib

matplotlib.use("Agg")
import matplotlib.gridspec as gridspec
import matplotlib.pyplot as plt
import numpy as np

logging.basicConfig(level=logging.INFO, format="%(asctime)s [VIZ] %(message)s")
log = logging.getLogger(__name__)

OUTPUT_DIR = os.environ.get("PLOT_DIR", "/tmp/fl_plots")


def load_results(path):
    if not os.path.exists(path):
        raise FileNotFoundError(f"{path} not found.")
    with open(path, "r") as f:
        return json.load(f)


def save_both(fig, filename, output_dir):
    os.makedirs(output_dir, exist_ok=True)

    tmp_path = os.path.join(output_dir, filename)
    local_path = os.path.join(os.getcwd(), filename)

    fig.savefig(tmp_path, dpi=150, bbox_inches="tight")
    fig.savefig(local_path, dpi=150, bbox_inches="tight")

    log.info(f"Saved → {tmp_path} AND {local_path}")


def plot_all(results, output_dir=OUTPUT_DIR):
    rounds = [r["round"] for r in results]
    loss = [r["loss"] for r in results]
    accuracy = [r["accuracy"] for r in results]
    acc_pct = [a * 100 for a in accuracy]

    # 🔥 NEW: convergence speed (delta accuracy)
    acc_diff = np.diff(acc_pct, prepend=acc_pct[0])

    # 🔥 NEW: client-wise variance (if available)
    client_var = []
    for r in results:
        if "client_accuracies" in r:
            client_var.append(np.var(r["client_accuracies"]))
        else:
            client_var.append(0)

    # ─────────────────────────────
    # 📊 MAIN DASHBOARD (3x2 grid)
    # ─────────────────────────────
    fig = plt.figure(figsize=(16, 11))
    fig.suptitle("Federated Learning Dashboard — FedCM", fontsize=16, fontweight="bold")

    gs = gridspec.GridSpec(3, 2, figure=fig, hspace=0.4, wspace=0.3)

    # 1️⃣ Accuracy
    ax1 = fig.add_subplot(gs[0, 0])
    ax1.plot(rounds, acc_pct, marker="o", color="#2563EB", linewidth=2)
    ax1.fill_between(rounds, acc_pct, alpha=0.1, color="#2563EB")
    ax1.set_title("Accuracy per Round", fontweight="bold")
    ax1.set_ylabel("Accuracy (%)")
    ax1.grid(True, linestyle="--", alpha=0.5)

    # 2️⃣ Loss
    ax2 = fig.add_subplot(gs[0, 1])
    ax2.plot(rounds, loss, marker="s", color="#DC2626", linewidth=2)
    ax2.fill_between(rounds, loss, alpha=0.1, color="#DC2626")
    ax2.set_title("Loss per Round", fontweight="bold")
    ax2.set_ylabel("Loss")
    ax2.grid(True, linestyle="--", alpha=0.5)

    # 3️⃣ Accuracy vs Loss
    ax3 = fig.add_subplot(gs[1, 0])
    ax3.plot(rounds, acc_pct, color="#2563EB", label="Accuracy")
    ax3.set_ylabel("Accuracy (%)", color="#2563EB")
    ax3b = ax3.twinx()
    ax3b.plot(rounds, loss, color="#DC2626", linestyle="--", label="Loss")
    ax3b.set_ylabel("Loss", color="#DC2626")
    ax3.set_title("Accuracy vs Loss")
    ax3.grid(True, linestyle="--", alpha=0.4)

    # 4️⃣ Final metrics
    final = results[-1]
    ax4 = fig.add_subplot(gs[1, 1])
    metrics = ["Accuracy (%)", "Loss"]
    values = [final["accuracy"] * 100, final["loss"]]
    ax4.bar(metrics, values, color=["#2563EB", "#DC2626"])
    ax4.set_title(f"Final Metrics (Round {final['round']})")
    ax4.grid(True, axis="y", linestyle="--", alpha=0.5)

    # 🔥 5️⃣ Convergence speed
    ax5 = fig.add_subplot(gs[2, 0])
    ax5.plot(rounds, acc_diff, marker="o", color="#059669")
    ax5.set_title("Convergence Speed (Δ Accuracy)")
    ax5.set_ylabel("Δ Accuracy (%)")
    ax5.set_xlabel("Round")
    ax5.grid(True, linestyle="--", alpha=0.5)

    # 🔥 6️⃣ Client variance
    ax6 = fig.add_subplot(gs[2, 1])
    ax6.plot(rounds, client_var, marker="o", color="#7C3AED")
    ax6.set_title("Client-wise Accuracy Variance")
    ax6.set_ylabel("Variance")
    ax6.set_xlabel("Round")
    ax6.grid(True, linestyle="--", alpha=0.5)

    save_both(fig, "fl_training_dashboard.png", output_dir)
    plt.close()

    # ─────────────────────────────
    # 📊 Standalone Convergence Plot
    # ─────────────────────────────
    fig2, ax = plt.subplots(figsize=(9, 5))
    ax.plot(rounds, acc_pct, label="Accuracy", color="#2563EB")
    ax.plot(rounds, acc_diff, label="Δ Accuracy", color="#059669")
    ax.set_title("Convergence Analysis")
    ax.set_xlabel("Round")
    ax.legend()
    ax.grid(True, linestyle="--", alpha=0.4)

    save_both(fig2, "convergence_analysis.png", output_dir)
    plt.close()

    log.info("All plots generated successfully!")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python visualize.py <path_to_results.json>")
        sys.exit(1)

    results = load_results(sys.argv[1])
    plot_all(results)
