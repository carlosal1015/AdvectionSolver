import matplotlib.pyplot as plt
import numpy as np

def load_data(sources):
    x_lst = []
    u_lst = []
    for source in sources:
        x, u = np.loadtxt(source, skiprows=1, delimiter= ',', unpack = True)
        x_lst.append(x)
        u_lst.append(u)
    return x_lst, u_lst


def plot_data(x1, y1, x2, y2, label1, label2, title):
    plt.plot(x1, y1, label=label1)
    plt.plot(x2, y2, label=label2)
    plt.xlabel(r"Position $x$")
    plt.ylabel(r"Quantity $Q$")
    plt.title(title)
    plt.grid()
    plt.legend()
    plt.savefig(label2 + ".png", dpi= 400)
    plt.close()
    return 0


def main():
    sources = ['analytical.txt', 'upwind.txt', 'lax.txt', 'beam.txt', 'fromm.txt', 'minmod.txt', 'sb.txt', 'mc.txt', 'vL.txt']
    x_lst, u_lst = load_data(sources)

    labels = ['Upwind', 'Lax-Wendroff', 'Beam-Warming', 'Fromm', 'MinMod', 'SuperBee', 'MC', 'van-Leer']
    for i in range(1, len(sources)):
        title = "Comparison between " + labels[i-1] + " and analytical solution"
        plot_data(x_lst[0], u_lst[0], x_lst[i], u_lst[i], "Analytical solution", labels[i-1], title)


main()