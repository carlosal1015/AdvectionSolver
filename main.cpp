// A program to solve the 1D linear advection equation with different methods and slope/flux limiters
#include "simulation.h"
#include "fluxes.h"
#include "loadData.h"

int main()
{
    vector<double> dist;
    dist = loadFromTxt("../../customDist.txt");
    simulation Test(0.8, 0.0, 2.0, dist);

    Test.iterate("upwind", 4.0);
    Test.save_data("../../data/testupwind.txt");

    simulation Ana(0.8, 400);
    cout << "Generation analytical solution!" << endl;
    Ana.save_data("../../data/analytical.txt");

    simulation Up(0.8, 400);
    cout << "----Upwind----" << endl;
    Up.iterate("upwind", 4.0);
    Up.save_data("../../data/upwind.txt");

    simulation Lax(0.8, 400);
    cout << "----Lax-Wendroff----" << endl;
    Lax.iterate("lax_wendroff", 4.0);
    Lax.save_data("../../data/lax.txt");

    simulation beam(0.8, 400);
    cout << "----Beam-Warming----" << endl;
    beam.iterate("beam_warming", 4.0);
    beam.save_data("../../data/beam.txt");

    simulation fro(0.8, 400);
    cout << "----Fromm----" << endl;
    fro.iterate("fromm", 4.0);
    fro.save_data("../../data/fromm.txt");

    simulation mimo(0.8, 400);
    cout << "----MinMod----" << endl;
    mimo.iterate("minmod", 4.0);
    mimo.save_data("../../data/minmod.txt");

    simulation sb(0.8, 400);
    cout << "----SuperBee----" << endl;
    sb.iterate("superbee", 4.0);
    sb.save_data("../../data/sb.txt");

    simulation mc(0.8, 400);
    cout << "----MC----" << endl;
    mc.iterate("mc", 4.0);
    mc.save_data("../../data/mc.txt");

    simulation vl(0.8, 400);
    cout << "----van-Leer----" << endl;
    vl.iterate("van_leer", 4.0);
    vl.save_data("../../data/vL.txt");
}