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
    plot(name, np.linspace(0, 1, len(lines)), numbers)
    return numbers

def plotfromfile(name):
    plot(name, np.linspace(0, 1, 101), numberfromfile(name))

# plot target function
plotfromfile("true_y")

plt.figure()
plt.plot(np.linspace(0, 1, 101), numberfromfile("Jacob_diff"), 'r')
#plt.plot(np.linspace(0, 1, 101), numberfromfile("GS_diff"), 'b')
#plt.plot(np.linspace(0, 1, 101), numberfromfile("SOR_diff"), 'c')
plt.legend(["Jacob_diff"])
plt.savefig("comp_diff.png")
plt.close()