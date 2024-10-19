# AdvectionSolver

This code solves the 1D advection equation using a finite volume approach.
It uses different numerical methods to approximate the flux between cells.
It is meant as a showcase of the methods involved and should not be seen as a
ready-to-use code for numerical simulation of physical systems described via
the 1D adv. eq.

## Features

- Switching between different Slope- and Fluxlimiters to get an easy side to
  side comparison of the methods used.
- Adjustments of simulation parameters like grid size and Courant number to see
  their effect on the quality of the solution.
- Periodic boundary conditions.
- Custom initial conditions $q\left(x, t=0\right)$ or a test problem that includes
  discontinuities as well as a wave.

## Slope- and Fluxlimiters

1. Simple Upwind
1. Lax-Wendroff
1. Beam-Warming
1. Fromm
1. MinMod
1. SuperBee
1. MC
1. VanLeer

## Code Manual

There are three parts to this program `createDist.cpp` stands on it's own and
can generate a `customDistribution` as the initial condition for the solver.

The main simulation uses CMake to build.
It includes the `main.cpp` aswell as the headers and source files in
`include/` and `src/`.
After compilation and execution of the binary, the resulting simulation data
can be found in the data dir.

Now `plotting.py` can be run.
This generates plots of the numerical versus the analytical solution in the
results directory.

```
git clone https://github.com/carlosal1015/AdvectionSolver
git switch develop
```
