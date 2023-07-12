# World Generate

## Install

```bash
conda create -n wg python=3.8
conda activate wg
./setup.sh
```

## Train

### with ray

```bash
export LD_LIBRARY_PATH="/home/chli/github/world-environment/lib/:$LD_LIBRARY_PATH"
cd script
ray start --head --port=9366
```

### without ray

```bash
python RLlib_Trainer.py
```

### Log

```bash
tensorboard --logdir ~/ray_results/ --host 0.0.0.0
```

## Enjoy it~
