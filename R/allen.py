import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.integrate import solve_ivp
import concurrent.futures
import logging
import os
import math

# ==============================================================================
# 0. SETUP & LOGGING
# ==============================================================================
os.makedirs("/mnt/user-data/outputs/", exist_ok=True)

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s [%(levelname)s] %(message)s',
    datefmt='%H:%M:%S'
)
logger = logging.getLogger(__name__)

def set_pub_theme():
    """Applies a publication-ready theme to Matplotlib"""
    sns.set_theme(style="whitegrid", rc={
        'axes.edgecolor': 'gray',
        'axes.linewidth': 1.0,
        # Removed the invalid 'panel.grid.minor' key here
        'legend.frameon': False,
        'axes.labelsize': 10,
        'axes.titlesize': 11,
        'axes.titleweight': 'bold',
        'figure.titlesize': 12,
        'figure.titleweight': 'bold'
    })

# ==============================================================================
# 1. CORE GILLESPIE LOGIC
# ==============================================================================

def make_state():
    return {
        "N": [0],
        "M": 1,
        "biofilm": [False]
    }

def run_gillespie_biofilm(pars, t_max, snapshot_times, seed=None):
    if seed is not None:
        np.random.seed(seed)
        
    state = make_state()
    t = 0.0
    t_init = np.nan
    
    snap_idx = 0
    n_snaps = len(snapshot_times)
    snap_data = []

    g, K = pars['g'], pars['K']
    rim, rdet, rmig = pars['rim'], pars['rdet'], pars['rmig']
    rmig2 = rmig / 2.0
    Nstar = pars['Nstar']

    def record_snapshot():
        snap_data.append({
            "time": snapshot_times[snap_idx],
            "Ntot": sum(state["N"]),
            "M": state["M"],
            "N_layers": list(state["N"])
        })

    while t < t_max:
        while snap_idx < n_snaps and snapshot_times[snap_idx] <= t:
            record_snapshot()
            snap_idx += 1
            
        if snap_idx >= n_snaps:
            break
            
        N = state["N"]
        M = state["M"]
        biofilm = state["biofilm"]
        
        props = []
        ev_types = []
        layers = []
        
        # 1=replic, 2=detach, 3=immigr, 4=migr_r, 5=migr_l
        for i in range(M):
            # Growth
            rep = g * N[i] * max(0, 1.0 - N[i] / K)
            if rep > 0:
                props.append(rep); ev_types.append(1); layers.append(i)
            # Detach
            if not biofilm[i] and N[i] > 0:
                det = rdet * N[i]
                props.append(det); ev_types.append(2); layers.append(i)
            # Immigrate
            if i == M - 1:
                props.append(rim); ev_types.append(3); layers.append(i)
                
        if M > 1:
            for i in range(M - 1):
                migr_r = rmig2 * N[i]
                if migr_r > 0:
                    props.append(migr_r); ev_types.append(4); layers.append(i)
            for i in range(1, M):
                migr_l = rmig2 * N[i]
                if migr_l > 0:
                    props.append(migr_l); ev_types.append(5); layers.append(i)

        alpha0 = sum(props)
        if alpha0 <= 0:
            t = t_max
            break

        # Time step
        r1, r2 = np.random.rand(2)
        tau = -math.log(r1) / alpha0
        t += tau

        # Event Selection
        target = r2 * alpha0
        cumsum = 0.0
        ev_idx = 0
        for i, p in enumerate(props):
            cumsum += p
            if cumsum >= target:
                ev_idx = i
                break
                
        ev_type = ev_types[ev_idx]
        e_layer = layers[ev_idx]

        # State Update
        if ev_type == 1:
            N[e_layer] += 1
        elif ev_type == 2:
            N[e_layer] = max(0, N[e_layer] - 1)
        elif ev_type == 3:
            N[e_layer] += 1
        elif ev_type == 4:
            if e_layer < M - 1:
                N[e_layer] = max(0, N[e_layer] - 1)
                N[e_layer + 1] += 1
        elif ev_type == 5:
            if e_layer > 0:
                N[e_layer] = max(0, N[e_layer] - 1)
                N[e_layer - 1] += 1

        # Check Transition
        if not biofilm[M - 1] and N[M - 1] >= Nstar:
            biofilm[M - 1] = True
            N.append(0)
            biofilm.append(False)
            state["M"] += 1
            
        if np.isnan(t_init) and state["M"] > 1:
            t_init = t

    while snap_idx < n_snaps:
        record_snapshot()
        snap_idx += 1

    return {"snapshots": snap_data, "t_init": t_init, "pars": pars}

# ==============================================================================
# 2. ODE AND ANALYTICS LOGIC
# ==============================================================================

def build_ode_system(pars, M_fixed):
    g, K, rim, rdet, rmig = pars['g'], pars['K'], pars['rim'], pars['rdet'], pars['rmig']
    
    def ode_func(t, y):
        dN = np.zeros(M_fixed)
        for i in range(M_fixed):
            growth = g * y[i] * (1.0 - y[i] / K)
            mig_in = 0.0
            mig_out = 0.0
            
            if i < M_fixed - 1: mig_in += (rmig / 2) * y[i + 1]
            if i > 0:           mig_in += (rmig / 2) * y[i - 1]
            if i < M_fixed - 1: mig_out += (rmig / 2) * y[i]
            if i > 0:           mig_out += (rmig / 2) * y[i]
            
            immig = rim if i == M_fixed - 1 else 0.0
            detach = rdet * y[i] if i == M_fixed - 1 else 0.0
            
            dN[i] = growth + mig_in - mig_out + immig - detach
        return dN
    return ode_func

def run_deterministic(pars, t_max, Nstar_tol=0.99):
    Nstar = pars['Nstar']
    M_cur = 1
    N_cur = [0.0]
    t_cur = 0.0
    out_dfs = []
    
    while t_cur < t_max and M_cur <= 15:
        ode_fn = build_ode_system(pars, M_cur)
        
        # Event function for threshold crossing
        def phase_transition(t, y):
            return y[M_cur - 1] - (Nstar * Nstar_tol)
        phase_transition.terminal = True
        phase_transition.direction = 1

        sol = solve_ivp(
            ode_fn, 
            [t_cur, t_max], 
            N_cur, 
            method='LSODA', 
            events=phase_transition,
            max_step=t_max/500 # Ensure decent resolution
        )
        
        df = pd.DataFrame(sol.y.T, columns=[f"L{i}" for i in range(M_cur)])
        df.insert(0, 'time', sol.t)
        out_dfs.append(df)
        
        if sol.status == 1: # Event reached
            t_cur = sol.t[-1]
            N_cur = list(sol.y[:, -1]) + [0.0]
            M_cur += 1
        else:
            break
            
    full_df = pd.concat(out_dfs, ignore_index=True)
    full_df['Ntot'] = full_df.drop('time', axis=1).sum(axis=1)
    full_df['M'] = full_df.drop(['time', 'Ntot'], axis=1).notna().sum(axis=1)
    return full_df

def deterministic_fixed_point(pars):
    g, K, rim, rdet = pars['g'], pars['K'], pars['rim'], pars['rdet']
    disc = 1 + 4 * rim / (g * K) / ((1 - rdet / g)**2)
    if np.isnan(disc) or disc < 0:
        return np.nan
    return (K / 2) * (1 - rdet / g) * (1 + math.sqrt(disc))

# ==============================================================================
# 3. DATA EXTRACTION WRAPPERS
# ==============================================================================

def extract_trajectory(sim_result):
    df = pd.DataFrame(sim_result["snapshots"])
    return df[['time', 'Ntot', 'M']]

def ensemble_summary(results):
    trajs = [extract_trajectory(r) for r in results]
    times = trajs[0]['time']
    Ntot_mat = np.column_stack([t['Ntot'] for t in trajs])
    M_mat = np.column_stack([t['M'] for t in trajs])
    
    return pd.DataFrame({
        'time': times,
        'Ntot_mean': Ntot_mat.mean(axis=1),
        'Ntot_sd': Ntot_mat.std(axis=1),
        'M_mean': M_mat.mean(axis=1),
        'M_sd': M_mat.std(axis=1)
    })

# Wrapper to unpack args for pool.map
def _run_single_wrapper(args):
    return run_gillespie_biofilm(*args)

def _run_sweep_wrapper(args):
    pars, t_max, snap_short, seed = args
    res = run_gillespie_biofilm(pars, t_max, snap_short, seed)
    return res['t_init'] if not np.isnan(res['t_init']) else t_max

# ==============================================================================
# 4. MAIN EXECUTION PIPELINE
# ==============================================================================

if __name__ == "__main__":
    set_pub_theme()

    pars_base = {
        'g': 0.083, 'K': 1000, 
        'rim': 0.083 * 1000 * 0.8, 'rdet': 0.083 * 0.5, 
        'rmig': 0.083 * 0.8, 'Nstar': 0.7 * 1000
    }
    pars_stoch = pars_base.copy()
    pars_stoch['Nstar'] = 1.17 * pars_base['K']

    g_val = pars_base['g']
    snap_times = np.linspace(0, 60 / g_val, 300)
    t_max_val = max(snap_times)

    # 4.1 Local Single Trajectories
    logger.info("Running single deterministic-regime trajectory (Local)...")
    sim_det = run_gillespie_biofilm(pars_base, t_max_val, snap_times, seed=7)
    
    logger.info("Running single stochastic-regime trajectory (Local)...")
    sim_stoch = run_gillespie_biofilm(pars_stoch, t_max_val, snap_times, seed=7)

    # 4.2 Parallel Ensembles
    num_workers = max(1, os.cpu_count() - 1)
    logger.info(f"Setting up parallel pool with {num_workers} cores...")
    
    np.random.seed(11)
    seeds_det = np.random.randint(0, 1e8, 10)
    args_det = [(pars_base, t_max_val, snap_times, s) for s in seeds_det]
    
    np.random.seed(22)
    seeds_stoch = np.random.randint(0, 1e8, 10)
    args_stoch = [(pars_stoch, t_max_val, snap_times, s) for s in seeds_stoch]

    with concurrent.futures.ProcessPoolExecutor(max_workers=num_workers) as executor:
        logger.info("Running ensemble (deterministic regime) in parallel...")
        ens_det = list(executor.map(_run_single_wrapper, args_det))
        
        logger.info("Running ensemble (stochastic regime) in parallel...")
        ens_stoch = list(executor.map(_run_single_wrapper, args_stoch))

    # 4.3 Deterministic ODEs
    logger.info("Running deterministic ODEs...")
    det_ode_det = run_deterministic(pars_base, t_max_val)
    det_ode_stoch = run_deterministic(pars_stoch, t_max_val)

    # 4.4 Initiation Times Parallel
    snap_short = np.linspace(0, t_max_val, 200)
    np.random.seed(55)
    
    args_init_det = [(pars_base, t_max_val, snap_short, s) for s in np.random.randint(0, 1e8, 150)]
    args_init_stoch = [(pars_stoch, t_max_val, snap_short, s) for s in np.random.randint(0, 1e8, 150)]

    with concurrent.futures.ProcessPoolExecutor(max_workers=num_workers) as executor:
        logger.info("Running initiation-time distributions in parallel...")
        tinit_det = np.array(list(executor.map(_run_sweep_wrapper, args_init_det)))
        tinit_stoch = np.array(list(executor.map(_run_sweep_wrapper, args_init_stoch)))

    # 4.5 Raster Plot Parallel
    np.random.seed(99)
    args_raster = [(pars_stoch, t_max_val, snap_times, s) for s in np.random.randint(0, 1e8, 15)]
    with concurrent.futures.ProcessPoolExecutor(max_workers=num_workers) as executor:
        logger.info("Running raster realizations in parallel...")
        ens_raster_stoch = list(executor.map(_run_single_wrapper, args_raster))

    logger.info("All simulations complete. Generating plots...")

    # ==============================================================================
    # 5. PLOTTING AND SAVING
    # ==============================================================================
    out_dir = "/mnt/user-data/outputs/"
    K_val = pars_base['K']

    # --- Figure 1: Single Trajectories ---
    fig, axes = plt.subplots(2, 1, figsize=(8, 6), sharex=True)
    td = extract_trajectory(sim_det)
    axes[0].plot(td['time'] * g_val, td['Ntot'] / K_val, color='#2166AC', lw=2)
    axes[0].axhline(pars_base['Nstar'] / K_val, color='firebrick', ls='--')
    axes[0].set_title('Single trajectory — deterministic regime (N*/K = 0.7)')
    axes[0].set_ylabel('$N_{tot} / K$')

    ts = extract_trajectory(sim_stoch)
    axes[1].plot(ts['time'] * g_val, ts['Ntot'] / K_val, color='#D6604D', lw=2)
    axes[1].axhline(pars_stoch['Nstar'] / K_val, color='firebrick', ls='--')
    axes[1].set_title('Single trajectory — stochastic regime (N*/K = 1.17)')
    axes[1].set_xlabel('Dimensionless time (gt)')
    axes[1].set_ylabel('$N_{tot} / K$')
    
    plt.tight_layout()
    plt.savefig(f"{out_dir}fig1_single_trajectories.png", dpi=150)
    plt.close()
    logger.info("Saved fig1")

    # --- Figure 3: Ensemble vs Deterministic ---
    sum_det = ensemble_summary(ens_det)
    sum_stoch = ensemble_summary(ens_stoch)
    
    fig, axes = plt.subplots(2, 1, figsize=(8, 6), sharex=True)
    
    # Det
    axes[0].fill_between(sum_det['time'] * g_val, 
                         (sum_det['Ntot_mean'] - sum_det['Ntot_sd'])/K_val,
                         (sum_det['Ntot_mean'] + sum_det['Ntot_sd'])/K_val, color='#AEC7E8', alpha=0.5)
    axes[0].plot(sum_det['time'] * g_val, sum_det['Ntot_mean']/K_val, color='#2166AC', lw=2)
    axes[0].plot(det_ode_det['time'] * g_val, det_ode_det['Ntot']/K_val, color='k', ls='--')
    axes[0].axhline(0.7, color='firebrick', ls=':')
    axes[0].set_title('Deterministic regime: ensemble mean ± SD vs ODE')
    
    # Stoch
    axes[1].fill_between(sum_stoch['time'] * g_val, 
                         (sum_stoch['Ntot_mean'] - sum_stoch['Ntot_sd'])/K_val,
                         (sum_stoch['Ntot_mean'] + sum_stoch['Ntot_sd'])/K_val, color='#FCBBA1', alpha=0.5)
    axes[1].plot(sum_stoch['time'] * g_val, sum_stoch['Ntot_mean']/K_val, color='#D6604D', lw=2)
    axes[1].plot(det_ode_stoch['time'] * g_val, det_ode_stoch['Ntot']/K_val, color='k', ls='--')
    axes[1].axhline(1.17, color='firebrick', ls=':')
    axes[1].set_title('Stochastic regime: ensemble mean ± SD vs ODE')
    axes[1].set_xlabel('gt')
    
    plt.tight_layout()
    plt.savefig(f"{out_dir}fig3_ensemble_vs_deterministic.png", dpi=150)
    plt.close()
    logger.info("Saved fig3")

    # --- Figure 6: Biofilm Thickness ---
    fig, axes = plt.subplots(1, 2, figsize=(9, 4), sharey=True)
    for res in ens_det:
        df = extract_trajectory(res)
        axes[0].plot(df['time'] * g_val, df['M'], color='#2166AC', alpha=0.5, lw=1)
    axes[0].set_title("Deterministic (N*/K=0.7)")
    axes[0].set_xlabel('gt')
    axes[0].set_ylabel('Number of layers M')

    for res in ens_stoch:
        df = extract_trajectory(res)
        axes[1].plot(df['time'] * g_val, df['M'], color='#D6604D', alpha=0.5, lw=1)
    axes[1].set_title("Stochastic (N*/K=1.17)")
    axes[1].set_xlabel('gt')
    
    plt.suptitle("Biofilm thickness (number of layers) vs time", fontweight='bold')
    plt.tight_layout()
    plt.savefig(f"{out_dir}fig6_biofilm_thickness.png", dpi=150)
    plt.close()
    logger.info("Saved fig6")

    # --- Figure 7: Initiation Times Histograms ---
    fig, axes = plt.subplots(1, 3, figsize=(11, 4))
    ti_det_valid = tinit_det[tinit_det < t_max_val * 0.99] * g_val
    ti_stoch_valid = tinit_stoch[tinit_stoch < t_max_val * 0.99] * g_val
    
    axes[0].hist(ti_det_valid, bins=30, color='#2166AC', edgecolor='white')
    axes[0].set_title('Det. Regime Initiation')
    axes[0].set_xlabel('Initiation time (gt)')
    
    axes[1].hist(ti_stoch_valid, bins=30, color='#D6604D', edgecolor='white', density=True)
    axes[1].set_title('Stoch. Regime Initiation')
    axes[1].set_xlabel('Initiation time (gt)')
    if len(ti_stoch_valid) > 5:
        rate = 1 / np.mean(ti_stoch_valid)
        x_vals = np.linspace(0, max(ti_stoch_valid), 100)
        axes[1].plot(x_vals, rate * np.exp(-rate * x_vals), 'k--', lw=2, label=f'Fit rate={rate:.3f}')
        axes[1].legend()

    axes[2].hist(ti_stoch_valid, bins=30, color='#D6604D', edgecolor='white', density=True)
    axes[2].set_yscale('log')
    axes[2].set_title('Stoch. Regime (Log Scale)')
    axes[2].set_xlabel('Initiation time (gt)')
    
    plt.tight_layout()
    plt.savefig(f"{out_dir}fig7_initiation_times.png", dpi=150)
    plt.close()
    logger.info("Saved fig7")

    # --- Figure 11: Raster Realizations ---
    rast_data = []
    t_inits_raster = []
    for i, res in enumerate(ens_raster_stoch):
        df = pd.DataFrame(res["snapshots"])
        df['rep'] = i
        df['Nrel'] = df['Ntot'] / K_val
        df['t_dim'] = df['time'] * g_val
        rast_data.append(df)
        
        idx = df[df['M'] > 1].index
        t_inits_raster.append(df.loc[idx[0], 't_dim'] if len(idx) > 0 else np.nan)
        
    df_raster = pd.concat(rast_data)
    # Pivot for heatmap
    heat_mat = df_raster.pivot(index='rep', columns='t_dim', values='Nrel')
    
    plt.figure(figsize=(9, 5))
    ax = sns.heatmap(heat_mat, cmap='magma', vmin=0, vmax=2, cbar_kws={'label': 'N/K'})
    # Add vertical lines for transitions
    for t_i in t_inits_raster:
        if not np.isnan(t_i):
            # approximate x position in heatmap index
            x_pos = np.abs(heat_mat.columns - t_i).argmin()
            ax.axvline(x_pos, color='white', lw=0.8, alpha=0.7)
            
    # Clean up x-axis labels (hide most of them)
    ax.set_xticks(np.linspace(0, len(heat_mat.columns)-1, 6))
    ax.set_xticklabels(np.round(heat_mat.columns[np.linspace(0, len(heat_mat.columns)-1, 6).astype(int)], 1))
    
    plt.title("Raster plot: 15 stochastic realisations (stoch. regime)\nWhite lines = biofilm initiation event", fontweight='bold')
    plt.xlabel("gt")
    plt.ylabel("Realisation")
    plt.tight_layout()
    plt.savefig(f"{out_dir}fig11_raster_realisations.png", dpi=150)
    plt.close()
    logger.info("Saved fig11")

    logger.info(f"Done! Plotting completed successfully in {out_dir}")