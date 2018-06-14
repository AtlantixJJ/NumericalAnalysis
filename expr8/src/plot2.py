import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_file(file_name):
    f = open(file_name)
    n = int(f.readline().strip())
    
    maxi_v = []
    v = []

    for l in f.readlines():
        items = l.strip().split(",")
        
        m_ = float(items[1].split(" ")[1])
        maxi_v.append(m_)

        v.append(np.array([float(it) for it in items[2:]]))

    return np.array(maxi_v), np.array(v)

def plot(name, x=None, y=None):
    plt.plot(x, y)
    plt.savefig(name+".png")
    plt.close()

def sigmoid(l):
    y = np.array([1. / (1. + np.exp(-x)) for x in l])
    y = y * 2 -1
    return y

maxi_v, v = read_file("data/log2.txt")

plt.plot(maxi_v, 'b.')
plt.savefig("fig/maxi_v_2.png")
plt.close()

ax = plt.gca(projection="3d")
print(v.shape)
ax.plot(v[:, 0], v[:, 1], v[:, 2], 'rx')
plt.savefig("fig/v_2.png")
plt.close()


