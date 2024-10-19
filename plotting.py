#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np


def load_data(data_path: str, sources: list):
    x_lst = []
    u_lst = []

    for source in sources:
        x, u = np.loadtxt(
            fname=data_path + source, skiprows=1, delimiter=",", unpack=True
        )
        x_lst.append(x)
        u_lst.append(u)
    return x_lst, u_lst


def plot_data(x1, y1, x2, y2, label1, label2, title, out_dir):
    plt.plot(x1, y1, label=label1)
    plt.plot(x2, y2, label=label2)
    plt.xlabel(r"Position $x$")
    plt.ylabel(r"Quantity $Q$")
    plt.title(label=title)
    plt.grid()
    plt.legend()
    plt.savefig(
        out_dir + label2 + ".pdf",
        transparent=True,
        bbox_inches="tight",
        dpi=400,
    )
    plt.close()
    return 0


def main():
    from platform import system

    if system() == "Windows":
        data_path = r".\build\bin\\"
    elif system() == "Linux":
        data_path = r"build/bin/"

    out_dir = "results/"
    sources = [
        "custom_analytical.txt",
        "custom_upwind.txt",
        "analytical.txt",
        "upwind.txt",
        "lax.txt",
        "beam.txt",
        "fromm.txt",
        "minmod.txt",
        "sb.txt",
        "mc.txt",
        "vL.txt",
    ]
    x_lst, u_lst = load_data(data_path, sources)
    x_lst, u_lst = load_data(data_path, sources)

    labels = [
        "Upwind",
        "Lax-Wendroff",
        "Beam-Warming",
        "Fromm",
        "MinMod",
        "SuperBee",
        "MC",
        "van-Leer",
    ]
    for i in range(3, len(sources)):
        title = "Comparison between " + labels[i - 3] + " and analytical solution"
        plot_data(
            x1=x_lst[2],
            y1=u_lst[2],
            x2=x_lst[i],
            y2=u_lst[i],
            label1="Analytical solution",
            label2=labels[i - 3],
            title=title,
            out_dir=out_dir,
        )

    plot_data(
        x1=x_lst[0],
        y1=u_lst[0],
        x2=x_lst[1],
        y2=u_lst[1],
        label1="Analytical solution",
        label2="Upwind_custom",
        title="Comparison between upwind and analytical for custom dist",
        out_dir=out_dir,
    )


main()
