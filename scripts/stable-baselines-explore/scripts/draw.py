import matplotlib.pyplot as plt
import numpy as np
        
with open('reward.txt', 'r') as f:
    lines = f.readlines()

    skip_num = int(len(lines) / 100)

    print('total episode : ', len(lines))

    line_size = int(len(lines) / skip_num)

    data = np.zeros((line_size, 2))

    for i in range(line_size):
        data[i][0] = skip_num * i
        value = 0
        for j in range(skip_num * i, skip_num * (i + 1)):
            value += float(lines[j])
        value /= skip_num
        data[i][1] = value

    plt.plot(data[:, 0], data[:, 1])
    plt.show()

# avg_num = 1000
        
# with open('reward.txt', 'r') as f:
#     lines = f.readlines()

#     print('total episode : ', len(lines))

#     line_size = len(lines)

#     data = np.zeros((line_size - avg_num + 1, 2))

#     for i in range(line_size - avg_num + 1):
#         data[i][0] = i
#         value = 0
#         for j in range(i, i + avg_num):
#             value += float(lines[j])
#         value /= avg_num
#         data[i][1] = value

#     plt.plot(data[:, 0], data[:, 1])
#     plt.show()