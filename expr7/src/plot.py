import numpy as np
import matplotlib.pyplot as plt

def plot(name, x=None, y=None):
    plt.plot(x, y)
    plt.savefig(name+".png")
    plt.close()

def numberfromfile(name):
    lines = open(name + ".txt", "r").readlines()

    numbers = []
    for l in lines:
        numbers.append(float(l.strip()))
    plot(name, np.linspace(-3, 3, len(lines)), numbers)
    return numbers

def plotfromfile(name):
    plot(name, np.linspace(-3, 3, 601), numberfromfile(name))

# plot target function
plotfromfile("data/f1_y")
plotfromfile("data/f3_y")

plt.figure()
#plt.plot(np.linspace(0, 1, 101), numberfromfile("data/f1_y"), 'r')
#plt.plot(np.linspace(0, 1, 101), numberfromfile("GS_diff"), 'b')
#plt.plot(np.linspace(0, 1, 101), numberfromfile("SOR_diff"), 'c')
#plt.legend(["f1"])
#plt.savefig("fig/f1_y.png")
plt.close()