# world-environment

## run with .so
```bash
export LD_LIBRARY_PATH="/home/chli/github/world-environment/lib/:$LD_LIBRARY_PATH"
```bash

## Install
```bash
conda create -n torch python=3.8
conda activate torch
pip install torch==1.10.0+cu113 torchvision==0.11.1+cu113 torchaudio==0.10.0+cu113 -f https://download.pytorch.org/whl/cu113/torch_stable.html
pip install opencv-python numpy stable-baselines3 gym tensorboard
```

## Build
```bash
cd lib
mkdir build
cd build
cmake ..
make -j
cp WorldEnvironment.* ../../script/WorldEnvironment.so
cd ../../script
```

## Run
```bash
python PPO_Trainer.py
tensorboard --logdir ./PPO_WE_tb/ --host 0.0.0.0 --port 6006
```

## Enjoy it~
