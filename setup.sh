cd ..
git clone https://github.com/pybind/pybind11.git

pip install torch==1.10.2+cu113 torchvision==0.11.3+cu113 torchaudio==0.10.2+cu113 -f https://download.pytorch.org/whl/cu113/torch_stable.html
pip install "ray[rllib]" "gym[atari]" "gym[accept-rom-license]" atari_py opencv-python numpy stable-baselines3 gym tensorboard pytest pybind11

cd pybind11
mkdir build
cd build
cmake ..
make -j
sudo make install
cd ../../world-generate/lib

mkdir build
cd build
cmake ..
make -j

cp WorldEnvironment.* ../../script/WorldEnvironment.so
