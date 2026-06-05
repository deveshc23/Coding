import os
import glob
import pandas as pd
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
import torchaudio
import torchaudio.transforms as T
from sklearn.model_selection import StratifiedKFold
from sklearn.metrics import f1_score
from tqdm.auto import tqdm
import soundfile as sf
import random

# ──────────────────────────────────────────────────────────────
# Reproducibility
# ──────────────────────────────────────────────────────────────
def seed_everything(seed=42):
    random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)
        torch.backends.cudnn.deterministic = True
        torch.backends.cudnn.benchmark = False

seed_everything(42)

device = torch.device('mps' if torch.backends.mps.is_available() else 'cuda' if torch.cuda.is_available() else 'cpu')

# ──────────────────────────────────────────────────────────────
# Configuration
# ──────────────────────────────────────────────────────────────
class Config:
    TRAIN_CSV = 'train.csv'
    TRAIN_AUDIO_DIR = 'train_audio/train_audio'
    TEST_CSV = 'sample_submission.csv'
    TEST_AUDIO_DIR = 'test_audio/test_audio'

    if not os.path.exists(TRAIN_AUDIO_DIR):
        TRAIN_AUDIO_DIR = 'train_audio'
    if not os.path.exists(TEST_AUDIO_DIR):
        TEST_AUDIO_DIR = 'test_audio'

    NUM_CLASSES = 10
    SAMPLE_RATE = 16000
    MAX_DURATION = 2.0
    N_MELS = 128
    N_FFT = 1024
    HOP_LENGTH = 160

    BATCH_SIZE = 64
    EPOCHS = 80
    LR = 1e-3
    WEIGHT_DECAY = 5e-4
    N_FOLDS = 5
    NUM_WORKERS = 0

    # ── augmentation (calibrated) ──
    MIXUP_PROB = 0.15
    CUTMIX_PROB = 0.10
    MIX_ALPHA = 0.3
    CUTMIX_ALPHA = 1.0
    LABEL_SMOOTHING = 0.05

    WAVE_NOISE_PROB = 0.25
    WAVE_NOISE_STD = 0.003
    TIME_MASK_PARAM = 20
    FREQ_MASK_PARAM = 15
    TIME_MASK_PROB = 0.35
    FREQ_MASK_PROB = 0.35
    RANDOM_GAIN_PROB = 0.3
    RANDOM_GAIN_DB = 3.0
    POLARITY_FLIP_PROB = 0.5

    # ── training ──
    GRAD_CLIP_NORM = 1.0
    PCT_START = 0.15
    DROPOUT = 0.15

    # ── TTA ──
    TTA_SHIFT_FRAMES = 5

# ──────────────────────────────────────────────────────────────
# Dataset with energy-aware cropping + calibrated augmentation
# ──────────────────────────────────────────────────────────────
class AudioDataset(Dataset):
    def __init__(self, df, audio_dir, is_train=True, is_test=False):
        self.df = df
        self.audio_dir = audio_dir
        self.is_train = is_train
        self.is_test = is_test
        self.max_frames = int(Config.SAMPLE_RATE * Config.MAX_DURATION)

        self.mel_spectrogram = T.MelSpectrogram(
            sample_rate=Config.SAMPLE_RATE,
            n_fft=Config.N_FFT,
            hop_length=Config.HOP_LENGTH,
            n_mels=Config.N_MELS
        )
        self.amplitude_to_db = T.AmplitudeToDB()
        self.time_masking = T.TimeMasking(time_mask_param=Config.TIME_MASK_PARAM)
        self.freq_masking = T.FrequencyMasking(freq_mask_param=Config.FREQ_MASK_PARAM)

    def __len__(self):
        return len(self.df)

    def _energy_aware_crop(self, waveform):
        """Center crop window on the speech energy peak instead of random position."""
        length = waveform.shape[1]
        if length <= self.max_frames:
            return waveform

        mono = waveform[0].abs()
        peak = torch.max(mono)
        if peak <= 1e-8:
            start = random.randint(0, length - self.max_frames)
            return waveform[:, start:start + self.max_frames]

        threshold = 0.15 * peak
        active = torch.where(mono > threshold)[0]
        if active.numel() == 0:
            start = random.randint(0, length - self.max_frames)
            return waveform[:, start:start + self.max_frames]

        center_idx = active[random.randint(0, active.numel() - 1)].item()
        left = center_idx - self.max_frames // 2
        left = max(0, min(left, length - self.max_frames))
        return waveform[:, left:left + self.max_frames]

    def _crop_or_pad(self, waveform):
        length = waveform.shape[1]
        if length > self.max_frames:
            if self.is_train:
                waveform = self._energy_aware_crop(waveform)
            else:
                start = (length - self.max_frames) // 2
                waveform = waveform[:, start:start + self.max_frames]
        elif length < self.max_frames:
            padding = self.max_frames - length
            if self.is_train:
                pad_left = random.randint(0, padding)
                pad_right = padding - pad_left
            else:
                pad_left = padding // 2
                pad_right = padding - pad_left
            waveform = F.pad(waveform, (pad_left, pad_right))
        return waveform

    def __getitem__(self, idx):
        row = self.df.iloc[idx]
        file_path = os.path.join(self.audio_dir, f"{row['id']}.wav")

        waveform, sr = sf.read(file_path, dtype='float32')
        if waveform.ndim > 1:
            waveform = waveform.mean(axis=1)
        waveform = torch.from_numpy(waveform).unsqueeze(0)

        if sr != Config.SAMPLE_RATE:
            resampler = T.Resample(sr, Config.SAMPLE_RATE)
            waveform = resampler(waveform)

        # ── waveform augmentations ──
        if self.is_train:
            # polarity flip (free, zero distortion)
            if random.random() < Config.POLARITY_FLIP_PROB:
                waveform = -waveform
            # random gain (±dB)
            if random.random() < Config.RANDOM_GAIN_PROB:
                gain_db = random.uniform(-Config.RANDOM_GAIN_DB, Config.RANDOM_GAIN_DB)
                waveform = waveform * (10.0 ** (gain_db / 20.0))
            # additive noise
            if random.random() < Config.WAVE_NOISE_PROB:
                noise = torch.randn_like(waveform) * Config.WAVE_NOISE_STD
                waveform = waveform + noise

        waveform = self._crop_or_pad(waveform)

        mel = self.mel_spectrogram(waveform)
        mel = self.amplitude_to_db(mel)

        # ── spectrogram augmentations ──
        if self.is_train:
            if random.random() < Config.TIME_MASK_PROB:
                mel = self.time_masking(mel)
            if random.random() < Config.FREQ_MASK_PROB:
                mel = self.freq_masking(mel)

        mel = (mel - mel.mean()) / (mel.std() + 1e-6)

        if not self.is_test:
            return mel, row['label']
        return mel

# ──────────────────────────────────────────────────────────────
# Model: ResNet-18 Slim [32,64,128,256] + SE Attention
# ──────────────────────────────────────────────────────────────
class SEBlock(nn.Module):
    """Squeeze-and-Excitation: lightweight channel attention."""
    def __init__(self, channels, reduction=4):
        super().__init__()
        mid = max(channels // reduction, 8)
        self.fc1 = nn.Linear(channels, mid, bias=False)
        self.fc2 = nn.Linear(mid, channels, bias=False)

    def forward(self, x):
        # x: (B, C, H, W)
        w = x.mean(dim=(2, 3))           # global avg pool → (B, C)
        w = F.relu(self.fc1(w), inplace=True)
        w = torch.sigmoid(self.fc2(w))
        return x * w.unsqueeze(-1).unsqueeze(-1)


class BasicBlock(nn.Module):
    def __init__(self, in_channels, out_channels, stride=1, use_se=True):
        super().__init__()
        self.conv1 = nn.Conv2d(in_channels, out_channels, kernel_size=3, stride=stride, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(out_channels)
        self.relu = nn.ReLU(inplace=True)
        self.conv2 = nn.Conv2d(out_channels, out_channels, kernel_size=3, stride=1, padding=1, bias=False)
        self.bn2 = nn.BatchNorm2d(out_channels)

        self.se = SEBlock(out_channels) if use_se else nn.Identity()

        self.shortcut = nn.Sequential()
        if stride != 1 or in_channels != out_channels:
            self.shortcut = nn.Sequential(
                nn.Conv2d(in_channels, out_channels, kernel_size=1, stride=stride, bias=False),
                nn.BatchNorm2d(out_channels)
            )

    def forward(self, x):
        identity = self.shortcut(x)
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)
        out = self.conv2(out)
        out = self.bn2(out)
        out = self.se(out)
        out += identity
        out = self.relu(out)
        return out


class CustomAudioNet(nn.Module):
    """ResNet-18 Slim: [2,2,2,2] blocks, [32,64,128,256] channels, SE attention.
    ~3M params — 7x smaller than the previous ResNet-34.
    """
    def __init__(self, num_classes=10):
        super().__init__()
        channels = [32, 64, 128, 256]
        blocks = [2, 2, 2, 2]

        self.in_channels = channels[0]
        self.conv1 = nn.Conv2d(1, channels[0], kernel_size=7, stride=2, padding=3, bias=False)
        self.bn1 = nn.BatchNorm2d(channels[0])
        self.relu = nn.ReLU(inplace=True)
        self.maxpool = nn.MaxPool2d(kernel_size=3, stride=2, padding=1)

        self.layer1 = self._make_layer(channels[0], blocks[0], stride=1)
        self.layer2 = self._make_layer(channels[1], blocks[1], stride=2)
        self.layer3 = self._make_layer(channels[2], blocks[2], stride=2)
        self.layer4 = self._make_layer(channels[3], blocks[3], stride=2)

        self.avgpool = nn.AdaptiveAvgPool2d((1, 1))
        self.dropout = nn.Dropout(Config.DROPOUT)
        self.fc = nn.Linear(channels[3], num_classes)

        self._initialize_weights()

    def _initialize_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Conv2d):
                nn.init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
            elif isinstance(m, nn.BatchNorm2d):
                nn.init.constant_(m.weight, 1)
                nn.init.constant_(m.bias, 0)
            elif isinstance(m, nn.Linear):
                nn.init.normal_(m.weight, 0, 0.01)
                if m.bias is not None:
                    nn.init.constant_(m.bias, 0)

    def _make_layer(self, out_channels, num_blocks, stride):
        layers = []
        layers.append(BasicBlock(self.in_channels, out_channels, stride, use_se=True))
        self.in_channels = out_channels
        for _ in range(1, num_blocks):
            layers.append(BasicBlock(out_channels, out_channels, 1, use_se=True))
        return nn.Sequential(*layers)

    def forward(self, x):
        x = self.conv1(x)
        x = self.bn1(x)
        x = self.relu(x)
        x = self.maxpool(x)

        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)
        x = self.layer4(x)

        x = self.avgpool(x)
        x = torch.flatten(x, 1)
        x = self.dropout(x)
        x = self.fc(x)
        return x

# ──────────────────────────────────────────────────────────────
# Mixup / CutMix (calibrated probabilities applied in training)
# ──────────────────────────────────────────────────────────────
def mixup_data(x, y, alpha=0.3):
    lam = np.random.beta(alpha, alpha)
    idx = torch.randperm(x.size(0)).to(x.device)
    return lam * x + (1 - lam) * x[idx], y, y[idx], lam

def mixup_criterion(criterion, pred, y_a, y_b, lam):
    return lam * criterion(pred, y_a) + (1 - lam) * criterion(pred, y_b)

def cutmix_data(x, y, alpha=1.0):
    lam = np.random.beta(alpha, alpha)
    idx = torch.randperm(x.size(0)).to(x.device)
    _, _, H, W = x.shape
    cut_w = int(W * np.sqrt(1 - lam))
    cx = random.randint(0, W)
    x1, x2 = max(cx - cut_w // 2, 0), min(cx + cut_w // 2, W)
    mixed = x.clone()
    mixed[:, :, :, x1:x2] = x[idx, :, :, x1:x2]
    lam = 1 - (x2 - x1) / W
    return mixed, y, y[idx], lam

# ──────────────────────────────────────────────────────────────
# Training loop (with gradient clipping)
# ──────────────────────────────────────────────────────────────
def train_one_epoch(model, loader, criterion, optimizer, scheduler, device):
    model.train()
    running_loss = 0.0
    all_targets, all_preds = [], []
    pbar = tqdm(loader, desc="Training", leave=False)
    for inputs, targets in pbar:
        inputs, targets = inputs.to(device), targets.to(device)
        optimizer.zero_grad()

        rand_prob = random.random()
        if rand_prob < Config.MIXUP_PROB:
            inputs, y_a, y_b, lam = mixup_data(inputs, targets, alpha=Config.MIX_ALPHA)
            outputs = model(inputs)
            loss = mixup_criterion(criterion, outputs, y_a, y_b, lam)
        elif rand_prob < Config.MIXUP_PROB + Config.CUTMIX_PROB:
            inputs, y_a, y_b, lam = cutmix_data(inputs, targets, alpha=Config.CUTMIX_ALPHA)
            outputs = model(inputs)
            loss = mixup_criterion(criterion, outputs, y_a, y_b, lam)
        else:
            outputs = model(inputs)
            loss = criterion(outputs, targets)

        loss.backward()
        # gradient clipping for stability
        torch.nn.utils.clip_grad_norm_(model.parameters(), Config.GRAD_CLIP_NORM)
        optimizer.step()
        scheduler.step()
        running_loss += loss.item()

        _, predicted = outputs.max(1)
        all_targets.extend(targets.cpu().numpy())
        all_preds.extend(predicted.cpu().numpy())

        pbar.set_postfix({'loss': f'{running_loss / (pbar.n + 1):.4f}'})

    epoch_f1 = f1_score(all_targets, all_preds, average='macro')
    return running_loss / len(loader), epoch_f1

def validate(model, loader, criterion, device):
    model.eval()
    running_loss = 0.0
    all_targets, all_preds = [], []
    with torch.no_grad():
        for inputs, targets in loader:
            inputs, targets = inputs.to(device), targets.to(device)
            outputs = model(inputs)
            loss = criterion(outputs, targets)
            running_loss += loss.item()

            _, predicted = outputs.max(1)
            all_targets.extend(targets.cpu().numpy())
            all_preds.extend(predicted.cpu().numpy())

    epoch_f1 = f1_score(all_targets, all_preds, average='macro')
    return running_loss / len(loader), epoch_f1

# ──────────────────────────────────────────────────────────────
# Test inference with shift-based TTA + weighted ensemble
# ──────────────────────────────────────────────────────────────
def predict_test(models, model_weights):
    if not models:
        return
    if os.path.exists(Config.TEST_CSV):
        test_df = pd.read_csv(Config.TEST_CSV)
    else:
        test_files = glob.glob(os.path.join(Config.TEST_AUDIO_DIR, '*.wav'))
        ids = [os.path.splitext(os.path.basename(f))[0] for f in test_files]
        test_df = pd.DataFrame({'id': ids})

    if len(test_df) == 0:
        return

    test_dataset = AudioDataset(test_df, Config.TEST_AUDIO_DIR, is_train=False, is_test=True)
    test_loader = DataLoader(test_dataset, batch_size=Config.BATCH_SIZE, shuffle=False, num_workers=0)

    all_preds = np.zeros((len(test_df), Config.NUM_CLASSES))
    weight_sum = sum(model_weights)
    shift = Config.TTA_SHIFT_FRAMES

    print(f"Running Inference with {len(models)} models (weighted ensemble + shift TTA)...")
    for model, w in zip(models, model_weights):
        model.eval()
        fold_probs = []
        with torch.no_grad():
            for inputs in tqdm(test_loader, desc="Predicting", leave=False):
                inputs = inputs.to(device)
                # TTA: original + time-flip + shift-right + shift-left
                p1 = F.softmax(model(inputs), dim=1)                                   # original
                p2 = F.softmax(model(torch.flip(inputs, dims=[-1])), dim=1)             # time-flip
                p3 = F.softmax(model(torch.roll(inputs, shift, dims=-1)), dim=1)        # shift right
                p4 = F.softmax(model(torch.roll(inputs, -shift, dims=-1)), dim=1)       # shift left
                # weighted average: full weight for original & flip, half for shifts
                probs = (1.0 * p1 + 1.0 * p2 + 0.5 * p3 + 0.5 * p4) / 3.0
                fold_probs.extend(probs.cpu().numpy())
        all_preds += np.array(fold_probs) * w

    all_preds /= weight_sum
    submission = pd.DataFrame({'id': test_df['id'], 'label': np.argmax(all_preds, axis=1)})
    submission.to_csv('submission_v3_slim.csv', index=False)
    print("Saved submission to submission_v3_slim.csv")

# ──────────────────────────────────────────────────────────────
# Training driver with OOF evaluation + weighted ensemble
# ──────────────────────────────────────────────────────────────
def run_training():
    if not os.path.exists(Config.TRAIN_CSV):
        return [], []

    train_df = pd.read_csv(Config.TRAIN_CSV)
    skf = StratifiedKFold(n_splits=Config.N_FOLDS, shuffle=True, random_state=42)
    models = []
    model_weights = []
    oof_preds = np.full(len(train_df), -1, dtype=np.int64)

    for fold, (train_idx, val_idx) in enumerate(skf.split(train_df, train_df['label'])):
        print(f"\n==================== Fold {fold + 1}/{Config.N_FOLDS} ====================")

        train_fold_df = train_df.iloc[train_idx].reset_index(drop=True)
        val_fold_df = train_df.iloc[val_idx].reset_index(drop=True)

        train_dataset = AudioDataset(train_fold_df, Config.TRAIN_AUDIO_DIR, is_train=True, is_test=False)
        val_dataset = AudioDataset(val_fold_df, Config.TRAIN_AUDIO_DIR, is_train=False, is_test=False)

        train_loader = DataLoader(train_dataset, batch_size=Config.BATCH_SIZE, shuffle=True, num_workers=0)
        val_loader = DataLoader(val_dataset, batch_size=Config.BATCH_SIZE, shuffle=False, num_workers=0)

        model = CustomAudioNet(num_classes=Config.NUM_CLASSES).to(device)
        criterion = nn.CrossEntropyLoss(label_smoothing=Config.LABEL_SMOOTHING)
        optimizer = torch.optim.AdamW(model.parameters(), lr=Config.LR, weight_decay=Config.WEIGHT_DECAY)

        scheduler = torch.optim.lr_scheduler.OneCycleLR(
            optimizer,
            max_lr=Config.LR,
            steps_per_epoch=len(train_loader),
            epochs=Config.EPOCHS,
            pct_start=Config.PCT_START,
            anneal_strategy='cos'
        )

        best_val_f1 = 0.0
        best_path = f'model_fold_{fold}_v3.pth'

        for epoch in range(Config.EPOCHS):
            train_loss, train_f1 = train_one_epoch(model, train_loader, criterion, optimizer, scheduler, device)
            val_loss, val_f1 = validate(model, val_loader, criterion, device)

            print(f"Epoch {epoch + 1:02d} | Train Loss: {train_loss:.4f} F1: {train_f1:.4f} | Val Loss: {val_loss:.4f} F1: {val_f1:.4f}")

            if val_f1 > best_val_f1:
                best_val_f1 = val_f1
                torch.save(model.state_dict(), best_path)

        model.load_state_dict(torch.load(best_path, weights_only=True))
        model.eval()
        models.append(model)
        model_weights.append(max(best_val_f1, 1e-6))

        # OOF predictions for this fold
        fold_val_preds = []
        with torch.no_grad():
            for val_inputs, _ in val_loader:
                val_inputs = val_inputs.to(device)
                logits = model(val_inputs)
                fold_val_preds.extend(logits.argmax(dim=1).cpu().numpy())
        oof_preds[val_idx] = np.array(fold_val_preds, dtype=np.int64)

        print(f"-> Fold {fold + 1} Best Val Macro F1: {best_val_f1:.4f}")

    # Print OOF summary
    valid_mask = oof_preds >= 0
    if np.any(valid_mask):
        oof_f1 = f1_score(train_df.loc[valid_mask, 'label'], oof_preds[valid_mask], average='macro')
        print(f"\n{'=' * 50}")
        print(f"OOF Macro F1: {oof_f1:.4f}")
        print(f"Mean fold F1: {np.mean(model_weights):.4f}")
        print(f"{'=' * 50}")

    return models, model_weights


if __name__ == '__main__':
    print(f"Using device: {device}")

    # Print model info
    tmp_model = CustomAudioNet()
    total_params = sum(p.numel() for p in tmp_model.parameters())
    print(f"Model: ResNet-18 Slim + SE  |  Params: {total_params:,}  |  ~{total_params * 4 / 1024 / 1024:.1f} MB")
    del tmp_model

    trained_models, weights = run_training()
    print("\nRunning Inference...")
    predict_test(trained_models, weights)
