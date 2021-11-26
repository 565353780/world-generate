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
pip install opencv-python numpy stable-baselines3 gym tensorboard pytest pybind11
git clone https://github.com/pybind/pybind11.git
cd pybind11
mkdir build
cd build
cmake ..
make -j
sudo make install
cd ../..

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
tensorboard --logdir ./tmp/ --host 0.0.0.0
```

## Enjoy it~
