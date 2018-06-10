import numpy as np

a = np.array([[0, 0.4, 0.2],
              [-0.25, 0, 0.5],
              [0.2, -0.3, 0]])

print(np.linalg.eig(a))

b = np.array([[5, 0, 0],
              [-0.25, 4, 0],
              [0.2, -0.3, 10]])

c = np.array([[4., 3, 0],
            [3, 4, -1],
            [0, -1, 4]])
b = np.array([[3], [5.], [-5]])

x = np.zeros((3, 1))

r = b - np.dot(c, x)
p = np.array(r)

print("solve")

def printf(t):
    for i in range(t.shape[0]):
        a = ""
        for j in range(t.shape[1]):
            a += "%.3f\t" % t[i][j]
        print(a)

cnt = 0
while True:
    print(cnt)
    print("r")
    printf(r.transpose())
    print("p")
    printf(p.transpose())
    print("x")
    printf(x.transpose())
    print("----")
    dotrk = np.dot(r.transpose(), r)
    a = dotrk / np.dot(p.transpose(), np.dot(c, p))
    x += a * p
    r -= a * np.dot(c, p)
    dotrk1 = np.dot(r.transpose(), r)
    p = r + dotrk1 / dotrk * p


    cnt += 1

    if abs(r).sum() < 0.001:
        break

