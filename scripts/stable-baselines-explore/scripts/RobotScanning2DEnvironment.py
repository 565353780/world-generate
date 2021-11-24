from PIL import Image, ImageTk
import numpy as np
import matplotlib.pyplot as plt
from math import sin, cos, pi, ceil
from cv2 import namedWindow, imshow, WINDOW_AUTOSIZE, waitKey
import random
from random import randint
import gym
from gym import spaces
import os
from stable_baselines.common.env_checker import check_env
from stable_baselines.common.policies import MlpPolicy, CnnPolicy, CnnLstmPolicy, CnnLnLstmPolicy
from stable_baselines.common.vec_env import DummyVecEnv, SubprocVecEnv, VecNormalize, VecFrameStack
from stable_baselines.common import make_vec_env
from stable_baselines import PPO2
from stable_baselines import results_plotter
from stable_baselines.bench import Monitor
from stable_baselines.results_plotter import load_results, ts2xy
from stable_baselines.common.noise import AdaptiveParamNoiseSpec
from stable_baselines.common.callbacks import BaseCallback

from RobotScanning2DRewardStrategy import RobotScanning2DRewardStrategy as RewardStrategy
from RobotScanning2DDoneStrategy import RobotScanning2DDoneStrategy as DoneStrategy

class SaveOnBestTrainingRewardCallback(BaseCallback):
    """
    Callback for saving a model (the check is done every ``check_freq`` steps)
    based on the training reward (in practice, we recommend using ``EvalCallback``).

    :param check_freq: (int)
    :param log_dir: (str) Path to the folder where the model will be saved.
      It must contains the file created by the ``Monitor`` wrapper.
    :param verbose: (int)
    """
    def __init__(self, check_freq: int, log_dir: str, verbose=1):
        super(SaveOnBestTrainingRewardCallback, self).__init__(verbose)
        self.check_freq = check_freq
        self.log_dir = log_dir
        self.save_path = os.path.join(log_dir, 'best_model')
        self.best_mean_reward = -np.inf

    def _init_callback(self) -> None:
        # Create folder if needed
        if self.save_path is not None:
            os.makedirs(self.save_path, exist_ok=True)

    def _on_step(self) -> bool:
        if self.n_calls % self.check_freq == 0:

          # Retrieve training reward
          x, y = ts2xy(load_results(self.log_dir), 'timesteps')
          if len(x) > 0:
              # Mean training reward over the last 100 episodes
              mean_reward = np.mean(y[-100:])
              if self.verbose > 0:
                print("Num timesteps: {}".format(self.num_timesteps))
                print("Best mean reward: {:.2f} - Last mean reward per episode: {:.2f}".format(self.best_mean_reward, mean_reward))

              # New best model, you could save the agent here
              if mean_reward > self.best_mean_reward:
                  self.best_mean_reward = mean_reward
                  # Example for saving best model
                  if self.verbose > 0:
                    print("Saving new best model to {}".format(self.save_path))
                  self.model.save(self.save_path)

        return True

# label of environment[i][j]:
#     [0]:
#         0:can not go to
#         1:can go to
#     [1]:
#         0:do not know the message
#         1:got the messages

class RobotScanning2DEnvironment(gym.Env):
    """Custom Environment that follows gym interface"""
    metadata = {'render.modes': ['human']}
    
    def __init__(self, map_file, seed=None, angle=60.0, distance=5, delta_angle=0.01, SELF_RENDER=True, TRAIN_MODE=False, init_max_move_num=100):
        super(RobotScanning2DEnvironment, self).__init__()

        # Define action and observation space
        # They must be gym.spaces objects
        # Example when using discrete actions:
        # self.action_space = spaces.Discrete(8)
        # Example for using image as input:
        # self.observation_space = spaces.Box(low=0, high=255,
        #                                     shape=(128, 128, 3), dtype=np.uint8)

        self.max_w = 200
        self.max_h = 200

        self.init_max_move_num = init_max_move_num
        self.add_move_time = 1
        self.add_max_move_num_per_episode_num = 50

        self.max_hit_obstacle_time = -1

        self.unknown_color = [0, 0, 0]
        self.free_color = [128, 128, 128]
        self.obstacle_color = [255, 255, 255]
        self.pose_color = [255, 0, 0]

        self.init_pose_fixed = False
        self.SHOW_IMAGE = False

        self.seed(seed)
        self.observation_space = None
        self.SELF_RENDER = SELF_RENDER
        self.TRAIN_MODE = TRAIN_MODE
        self.total_reward = 0
        
        self.raw_map_file = map_file
        self.observation = None
        self.global_map = None
        self.output_image = None

        self.sight_angle = angle
        self.sight_distance = distance
        self.delta_ray_angle = delta_angle
        self.init_pose = np.array([1.0, 1.0, 0.0], dtype=np.float64)
        self.current_pose = self.init_pose.copy()

        self.action_space = None
        self.action_spaces = None

        self.load_map()
        self.init_action_space()

        self.reward_strategy = RewardStrategy(self.global_map)
        self.done_strategy = DoneStrategy(self.global_map)

        self.path = [self.current_pose.copy()]

        self.namedWindow = None

        self.hit_obstacle_time = 0
        self.total_move_num = 0
        self.finish_episode = 0

        self.test_idx = 0

        # 0:free 1:unknown 2:obstacle 3:position
        self.observation_output = np.zeros(self.observation_space.shape)
        self.free_label = [255, 0, 0, 0]
        self.unknown_label = [0, 255, 0, 0]
        self.obstacle_label = [0, 0, 255, 0]
        self.pose_label = [0, 0, 0, 255]

        # self.reward_range = [-1000, 1000]

    def init_action_space(self):
        self.action_space = spaces.Discrete(8)
        self.action_spaces = np.empty((8, 3), dtype=np.float64)
        self.action_spaces[0] = [1.0, 0.0, 90.0]
        self.action_spaces[1] = [-1.0, 0.0, -90.0]
        self.action_spaces[2] = [0.0, -1.0, 180.0]
        self.action_spaces[3] = [0.0, 1.0, 0.0]
        self.action_spaces[4] = [1.0, -1.0, 135.0]
        self.action_spaces[5] = [1.0, 1.0, 45.0]
        self.action_spaces[6] = [-1.0, -1.0, -135.0]
        self.action_spaces[7] = [-1.0, 1.0, -45.0]
        # self.action_spaces[8] = [2.0, 0.0, 90.0]
        # self.action_spaces[9] = [-2.0, 0.0, -90.0]
        # self.action_spaces[10] = [0.0, -2.0, 180.0]
        # self.action_spaces[11] = [0.0, 2.0, 0.0]

    def get_num_actions(self):
        return len(self.action_spaces)
        # return self.action_space.n
    
    def update_observation_output(self):
        for i in range(self.observation_output.shape[0]):
            for j in range(self.observation_output.shape[1]):
                if all(self.observation[i][j] == self.free_color):
                    self.observation_output[i][j] = self.free_label
                elif all(self.observation[i][j] == self.unknown_color):
                    self.observation_output[i][j] = self.unknown_label
                elif all(self.observation[i][j] == self.obstacle_color):
                    self.observation_output[i][j] = self.obstacle_label
                # elif all(self.observation[i][j] == self.pose_color):
                #     self.observation_output[i][j] = self.pose_label
        
        self.observation_output[:][:][3] = 0

        path_num = len(self.path)
        for i in range(min(path_num, 255)):
            [x, y] = self.path[path_num - i - 1][:2]
            if self.observation_output[int(x)][int(y)][3] == 0:
                self.observation_output[int(x)][int(y)][3] = 255 - i

    def step(self, action):
        if action not in range(len(self.action_spaces)):
        # if action not in range(self.action_space.n):
            print("Error action!")
            return (None, None, None, dict())
        else:
            self.total_move_num += 1

            target_pose = self.current_pose.copy()
            target_pose[:2] += self.action_spaces[action][:2]

            if not 0 <= int(target_pose[0]) < self.global_map.shape[0] or not 0 <= int(target_pose[1]) < self.global_map.shape[1]:

                self.hit_obstacle_time = 0

                self.total_reward -= 100.0

                self.debug()

                self.output(False)

                self.total_reward = 0

                self.total_move_num = 0

                self.finish_episode += 1

                self.update_observation_output()

                # return (self.observation, -100, True, dict())
                return (self.observation_output, -100, True, dict())

            if self.global_map[int(target_pose[0])][int(target_pose[1])][0] == 0 and (self.hit_obstacle_time < self.max_hit_obstacle_time or self.max_hit_obstacle_time == -1):

                self.hit_obstacle_time += 1

                self.total_reward -= 10.0

                self.debug()

                done = False

                if self.total_move_num >= self.max_move_num:
                    done = True

                if done:
                    self.hit_obstacle_time = 0

                    self.output(True)
                    
                    self.total_reward = 0

                    self.total_move_num = 0

                    self.finish_episode += 1
                
                self.update_observation_output()

                # return (self.observation, -10.0, done, dict())
                return (self.observation_output, -10.0, done, dict())

            target_pose[2] = self.action_spaces[action][2]

            self.update_observation(target_pose)

            self.current_pose = target_pose.copy()

            reward = self.reward_strategy.compute_reward(self.current_pose, self.observation)
            done = self.done_strategy.is_done(self.current_pose, self.observation)

            last_path = self.path[len(self.path) - 1]

            self.path.append(self.current_pose.copy())

            self.observation[int(last_path[0])][int(last_path[1])] = self.free_color
            self.observation[int(self.current_pose[0])][int(self.current_pose[1])] = self.pose_color

            if self.total_move_num >= self.max_move_num:
                done = True
            
            self.total_reward += reward

            self.debug()

            if done:

                self.hit_obstacle_time = 0

                self.output(True)
                
                self.total_reward = 0

                self.total_move_num = 0

                self.finish_episode += 1
            
            self.update_observation_output()

            # return (self.observation, reward, done, dict())
            return (self.observation_output, reward, done, dict())

    def debug(self):
        if False:
            print('total reward : ', self.total_reward)
            print('total_move_num : ', self.total_move_num)

    def output(self, done):
        if self.TRAIN_MODE:
            with open('reward.txt', 'a+') as f:
                f.write(str(int(self.total_reward)))
                f.write('\n')
        
        if not done:
            print('')
        print("Total Reward : ", self.total_reward)
        print("Total Step : ", self.total_move_num)
        print("======================================")

    def reset(self):
        self.observation = np.zeros(self.global_map.shape, dtype=np.int32)
        # self.update_observation(self.init_pose)

        if self.init_pose_fixed:
            test_pose = [[int(0.45 * self.max_h), int(0.1 * self.max_w), 0], [int(0.55 * self.max_h), int(0.1 * self.max_w), 0]]

            random_pose = test_pose[self.test_idx]
            self.test_idx = (self.test_idx + 1) % len(test_pose)

        else:
            rand_w_l = int(0.1 * self.max_w)
            rand_w_r = int(0.9 * self.max_w)
            rand_h_l = int(0.1 * self.max_h)
            rand_h_r = int(0.9 * self.max_h)
            random_pose = np.array([randint(rand_h_l, rand_h_r), randint(rand_w_l, rand_w_r), 0], dtype=np.float64)
            while self.global_map[int(random_pose[0])][int(random_pose[1])][0] == 0:
                random_pose[0] = randint(rand_h_l, rand_h_r)
                random_pose[1] = randint(rand_w_l, rand_w_r)

        self.init_pose = random_pose.copy()

        self.current_pose = self.init_pose.copy()

        self.path = []
        self.path.append(self.current_pose.copy())

        if self.finish_episode % self.add_max_move_num_per_episode_num == 0:
            self.max_move_num = self.init_max_move_num + self.add_move_time * int(self.finish_episode / self.add_max_move_num_per_episode_num)
        
        if self.max_move_num > self.global_map.shape[0] * self.global_map.shape[1]:
            self.max_move_num = self.global_map.shape[0] * self.global_map.shape[1]

        print('max move num : ', self.max_move_num)

        self.update_observation_output()

        # return self.observation
        return self.observation_output

    def seed(self, seed=None):
        if seed is not None:
            random.seed(seed)

    def load_map(self):

        img = Image.open(self.raw_map_file)
        img = img.convert("RGB")
        max_scale = self.max_w / img.size[0]
        if self.max_h / img.size[1] < max_scale:
            max_scale = self.max_h / img.size[1]

        if max_scale < 1:
            img = img.resize((int(img.size[0]*max_scale), int(img.size[1]*max_scale)), resample=Image.LANCZOS)

        self.max_w = img.size[0]
        self.max_h = img.size[1]

        self.global_map = self.transform_between_image_coordinate_and_map_coordinate(np.array(img))

        for i in range(self.global_map.shape[0]):
            for j in range(self.global_map.shape[1]):
                if self.global_map[i][j][0] < 200 or self.global_map[i][j][1] < 200 or self.global_map[i][j][2] < 200:
                    self.global_map[i][j] = [0, 0, 0]
                else:
                    self.global_map[i][j] = [255, 255, 255]

        self.add_boundary()

        # self.observation_space = spaces.Box(low=0, high=255, shape=(img.size[0], img.size[1], 3), dtype=np.uint8)
        self.observation_space = spaces.Box(low=0, high=255, shape=(img.size[0], img.size[1], 4), dtype=np.uint8)

        self.max_move_num = self.global_map.shape[0] * self.global_map.shape[1]

        # imshow('test', self.global_map)
        # waitKey()

    def add_boundary(self):
        self.global_map[0] = 0
        self.global_map[-1] = 0
        self.global_map[:, 0] = 0
        self.global_map[:, -1] = 0

    def transform_between_image_coordinate_and_map_coordinate(self, input_array):
        output_array = np.empty(input_array.shape, dtype=np.uint8)
        height = input_array.shape[0]
        width = input_array.shape[1]
        for i in range(height):
            for j in range(width):
                output_array[i][j] = np.uint8(input_array[height - 1 - i][j])
        
        return output_array

    def add_new_end_point(self, end_points, center_position, ray_angle):
        new_end_point_x = int(center_position[0] + self.sight_distance * sin(ray_angle * pi / 180.0))
        new_end_point_y = int(center_position[1] + self.sight_distance * cos(ray_angle * pi / 180.0))
        if end_points is None or len(end_points) == 0:
            return np.array([[new_end_point_x, new_end_point_y]], dtype=np.int32)
        else:
            if new_end_point_x != end_points[-1, 0] or new_end_point_y != end_points[-1, 1]:
                return np.append(end_points, [[new_end_point_x, new_end_point_y]], axis=0)
            else:
                return end_points

    def compute_ray_end_points(self, target_pose):
        ray_angle_right = target_pose[2] - self.sight_angle / 2.0
        ray_angle_left = target_pose[2] + self.sight_angle / 2.0
        # ray_num = ceil((ray_angle_left - ray_angle_right) / self.delta_ray_angle) + 1

        # end_points = self.add_new_end_point(None, target_pose[:2], ray_angle_right)
        end_points = None

        #for i in range(1, ray_num - 1):
        for ray_angle in np.arange(ray_angle_right, ray_angle_left, self.delta_ray_angle):
            end_points = self.add_new_end_point(end_points, target_pose[:2], ray_angle)

        end_points = self.add_new_end_point(end_points, target_pose[:2], ray_angle_left)

        return end_points

    def end_points_based_ray_cast(self, target_pose):
        end_points = self.compute_ray_end_points(target_pose)

        for i in range(len(end_points)):
            ray = end_points[i] - target_pose[:2]
            self.single_ray_cast(target_pose[:2], ray)

    def single_ray_cast(self, start_point, ray):
        long_axis_length = np.max(np.abs(ray))
        moving_unit = ray / long_axis_length

        for j in range(int(long_axis_length) + 1):
            if self.global_map[int(start_point[0] + moving_unit[0] * j)][int(start_point[1] + moving_unit[1] * j)][0] == 0:
                self.observation[int(start_point[0] + moving_unit[0] * j)][int(start_point[1] + moving_unit[1] * j)] = self.obstacle_color
                break
            else:
                self.observation[int(start_point[0] + moving_unit[0] * j)][int(start_point[1] + moving_unit[1] * j)] = self.free_color

    def uniform_angle_based_ray_cast(self, target_pose):
        ray_angle_right = target_pose[2] - self.sight_angle / 2.0
        ray_angle_left = target_pose[2] + self.sight_angle / 2.0

        for ray_angle in np.arange(ray_angle_right, ray_angle_left, self.delta_ray_angle):
            ray = [self.sight_distance * sin(ray_angle * pi / 180.0), self.sight_distance * cos(ray_angle * pi / 180.0)]
            self.single_ray_cast(target_pose[:2], ray)

        ray = [self.sight_distance * sin(ray_angle_left * pi / 180.0), self.sight_distance * cos(ray_angle_left * pi / 180.0)]
        self.single_ray_cast(target_pose[:2], ray)

    def update_observation(self, target_pose):
        if not 0 <= target_pose[0] < self.global_map.shape[0] or not 0 <= target_pose[1] < self.global_map.shape[1]:
            # print("Target pose out of range!")
            return

        self.end_points_based_ray_cast(target_pose)
        # self.uniform_angle_based_ray_cast(target_pose)

        self.current_pose = target_pose.copy()

    def paint_color(self):
        self.output_image = self.global_map.copy()
        # self.output_image[np.where(self.observation == 1)] = 255
        for i in range(self.output_image.shape[0]):
            for j in range(self.output_image.shape[1]):
                if all(self.observation[i][j] == self.free_color):
                    self.output_image[i][j] = [0, 0, 255]

        for pose in self.path:
            self.output_image[int(pose[0])][int(pose[1])] = [0, 255, 0]

        self.output_image = self.transform_between_image_coordinate_and_map_coordinate(self.output_image)

    def render(self, mode='human'):
        self.paint_color()

        if self.SELF_RENDER:
            if not self.SHOW_IMAGE:
                self.namedWindow = namedWindow('test_environment', WINDOW_AUTOSIZE)
                self.SHOW_IMAGE = True

            imshow('test_environment', self.output_image)
            waitKey(1)

        return self.output_image

        # plt.imshow(self.output_image)
        # plt.axis('off')
        # plt.show()

    def close (self):
        pass

    def test(self, position, forward_direction, show_image=False):

        if self.global_map is None:

            self.reset()

        target_pose = [position[0], position[1], forward_direction]
        self.update_observation(target_pose)

        if show_image:
            # self.show_output_image()
            self.render()

if __name__ == "__main__":

    game_name = "My2DEnv"
    # game_name = "CartPole-v1"
    # game_name = "Breakout-v0"

    train_mode = True
    policy = CnnPolicy
    init_max_move_num = 654

    log_dir = "./tmp/"
    os.makedirs(log_dir, exist_ok=True)

    start_episode = 0

    total_time_step =2500000

    num_cpu = 16

    global_seeds = 0

    def set_global_seeds(seed=0):
        global_seeds = seed

    def make_env(rank, seed=0, SELF_RENDER=False):
        def _init():
            env = RobotScanning2DEnvironment(map_file="./32x32.png", seed=seed+rank, angle=60.0, distance=5, delta_angle=0.01, SELF_RENDER=SELF_RENDER, TRAIN_MODE=train_mode, init_max_move_num=init_max_move_num)
            return env
        set_global_seeds(seed)
        return _init
    
    def make_framestack_env(rank, seed=0, SELF_RENDER=False):
        def _init():
            env = RobotScanning2DEnvironment(map_file="./32x32.png", seed=seed+rank, angle=60.0, distance=5, delta_angle=0.01, SELF_RENDER=SELF_RENDER, TRAIN_MODE=train_mode, init_max_move_num=init_max_move_num)
            env = DummyVecEnv([lambda : env])
            env = VecFrameStack(env, n_stack=4)
            return env
        set_global_seeds(seed)
        return _init

    env = None
    if game_name == "My2DEnv":
        if train_mode:
            if policy == CnnLnLstmPolicy or policy == CnnLstmPolicy:
                env = SubprocVecEnv([make_env(10, i) for i in range(num_cpu)])
            elif  policy == CnnPolicy:
                # env = DummyVecEnv([lambda : RobotScanning2DEnvironment(map_file="./32x32.png", seed=10, angle=60.0, distance=5, delta_angle=0.01, SELF_RENDER=False, TRAIN_MODE=train_mode)])
                env = SubprocVecEnv([make_env(10, i) for i in range(num_cpu)])
                # env = VecFrameStack(env, n_stack=4)
        else:
            if policy == CnnLnLstmPolicy or policy == CnnLstmPolicy:
                env = SubprocVecEnv([make_env(10, i) for i in range(num_cpu)])
            elif  policy == CnnPolicy:
                env = RobotScanning2DEnvironment(map_file="./32x32.png", seed=10, angle=60.0, distance=5, delta_angle=0.01, SELF_RENDER=True, TRAIN_MODE=train_mode, init_max_move_num=init_max_move_num)
                # env = Monitor(env, log_dir, info_keywords=('as', 'ac', 'rc'))
                env = DummyVecEnv([lambda : env])
                # env = VecFrameStack(env, n_stack=4)
    else:
        if train_mode:
            env = make_vec_env(game_name, n_envs=4)
        else:
            env = make_vec_env(game_name, n_envs=1)

    # check_env(env)

    model = None
    start_step_num = 0

    if start_episode > 0:
        model = PPO2.load("PPO2_" + game_name + "_" + str(start_episode), env)
    else:
        file_list = os.listdir(os.getcwd())

        for file_name in file_list:
            if "PPO2_" + game_name + "_" in file_name:
                current_step_num = int(file_name.split(".")[0].split("_")[2])

                if current_step_num > start_step_num:
                    start_step_num = current_step_num
        
        if start_step_num > 0:
            model = PPO2.load("PPO2_" + game_name + "_" + str(start_step_num), env)
        else:
            if game_name == "My2DEnv":
                model = PPO2(policy, env, verbose=1)
            else:
                model = PPO2(MlpPolicy, env, verbose=1)

    # callback = SaveOnBestTrainingRewardCallback(check_freq=1000, log_dir=log_dir)

    if train_mode:
        round = 0

        model.learning_rate = 1e-4

        while True:
            # model.learn(total_timesteps=total_time_step, callback=callback)
            model.learn(total_timesteps=total_time_step)

            try:
                os.remove("PPO2_" + game_name + "_" + str(start_step_num + round * total_time_step) + ".zip")
            except:
                pass

            round += 1
            
            model.save("PPO2_" + game_name + "_" + str(start_step_num + round * total_time_step))

        del model
    else:

        # results_plotter.plot_results([log_dir], total_time_step, results_plotter.X_TIMESTEPS, "PPO2 My2DEnv")
        # plt.show()

        while True:
            obs = env.reset()
            if policy == CnnLnLstmPolicy or policy == CnnLstmPolicy:
                done = [False, False]
                while not all(done):
                    action, _states = model.predict(obs)
                    obs, rewards, dones, info = env.step(action)
                    env.render('human')
                    done = dones
            else:
                done = False
                while not done:
                    action, _states = model.predict(obs)
                    obs, rewards, dones, info = env.step(action)
                    env.render()
                    done = dones


    # env.reset()

    # env.test(position=[70, 10], forward_direction=0, show_image=True)
    # env.reset()
    # env.test(position=[7, 7], forward_direction=0, show_image=True)
    # env.test(position=[40, 7], forward_direction=30, show_image=True)

'''
3.4GHz 每个线程训练速度为 3w steps / h

目前为 16线程 训练速度为 48w steps / h

每个完整 episode 从训练初期 100 steps 到后期 1024 steps，即
训练初期 4800 episodes / h
训练后期 168 episodes / h

平均下来测试一次需训练 20w episodes, 需要约 200 h 即 8.3 days
'''
