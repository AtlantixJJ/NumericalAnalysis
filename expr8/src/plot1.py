import numpy as np
import matplotlib.pyplot as plt

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

maxi_v, v = read_file("data/log1.txt")

plt.plot(maxi_v, 'b.')
plt.savefig("fig/maxi_v_1.png")
plt.close()

plt.plot(maxi_v/maxi_v[-1], 'b.')
plt.plot(sigmoid(range(0, maxi_v.shape[0])))
plt.savefig("fig/maxi_d_1.png")
plt.close()

plt.plot(sigmoid(range(-10, 10, 1)))
plt.savefig("fig/sigmoid.png")
plt.close()

ax = plt.gca()
for i in range(2, maxi_v.shape[0]):
    ax.arrow(v[i-1, 0], v[i-1, 1], v[i, 0] - v[i-1, 0], v[i, 1] - v[i-1, 1],
        length_includes_head=True, head_width=0.01, head_length=0.05, fc='r', ec='b')
ax.axis([0.4, 1, -1.2, -0.4])
plt.savefig("fig/v_1.png")
plt.close()


