import matplotlib.pyplot as plt

file = open("output.dat")

xs = []
ys = []
for line in file.readlines():
    xs.append(line.split(" ")[0])
    ys.append(line.split(" ")[1])

plt.plot(xs, ys, "-o")
plt.xlabel("SNR (dB)")
plt.ylabel("Signal capacity")
plt.show()
file.close()