import matplotlib.pyplot as plt
import numpy as np


def load_data(data_path, sources):
    x_lst = []
    u_lst = []
    for source in sources:
        x, u = np.loadtxt(data_path + source, skiprows=1,
                          delimiter=',', unpack=True)
        x_lst.append(x)
        u_lst.append(u)
    return x_lst, u_lst


def plot_data(x1, y1, x2, y2, label1, label2, title, out_dir):
    plt.plot(x1, y1, label=label1)
    plt.plot(x2, y2, label=label2)
    plt.xlabel(r"Position $x$")
    plt.ylabel(r"Quantity $Q$")
    plt.title(title)
    plt.grid()
    plt.legend()
    plt.savefig(out_dir + label2 + ".png", dpi=400)
    plt.close()
    return 0


def main():
    data_path = 'data/'
    out_dir = 'results/'
    sources = ['custom_analytical.txt', 'custom_upwind.txt', 'analytical.txt', 'upwind.txt', 'lax.txt', 'beam.txt',
               'fromm.txt', 'minmod.txt', 'sb.txt', 'mc.txt', 'vL.txt']
    x_lst, u_lst = load_data(data_path, sources)
    x_lst, u_lst = load_data(data_path, sources)

    labels = ['Upwind', 'Lax-Wendroff', 'Beam-Warming',
              'Fromm', 'MinMod', 'SuperBee', 'MC', 'van-Leer']
    for i in range(3, len(sources)):
        title = "Comparison between " + \
            labels[i-3] + " and analytical solution"
        plot_data(x_lst[2], u_lst[2], x_lst[i], u_lst[i],
                  "Analytical solution", labels[i-3], title, out_dir)
    plot_data(x_lst[0], u_lst[0], x_lst[1], u_lst[1], "Analytical solution", "Upwind_custom", "Comparison between upwind and analytical for custom dist", out_dir)


main()
