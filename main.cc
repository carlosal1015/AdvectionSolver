// A program to solve the 1D linear advection equation with different methods
// and slope/flux limiters
#include "fluxes.hh"
#include "loadData.hh"
#include "simulation.hh"

int main()
{
  std::vector<double> dist;
  dist = loadFromTxt("../customDist.txt");
  simulation custom(0.8, 0.0, 2.0, dist);
  custom.save_data("custom_analytical.txt");
  custom.iterate("upwind", 4.0);
  custom.save_data("custom_upwind.txt");

  simulation Ana(0.8, 400);
  std::cout << "Generation analytical solution!" << std::endl;
  Ana.save_data("analytical.txt");

  simulation Up(0.8, 400);
  std::cout << "----Upwind----" << std::endl;
  Up.iterate("upwind", 4.0);
  Up.save_data("upwind.txt");

  simulation Lax(0.8, 400);
  std::cout << "----Lax-Wendroff----" << std::endl;
  Lax.iterate("lax_wendroff", 4.0);
  Lax.save_data("lax.txt");

  simulation beam(0.8, 400);
  std::cout << "----Beam-Warming----" << std::endl;
  beam.iterate("beam_warming", 4.0);
  beam.save_data("beam.txt");

  simulation fro(0.8, 400);
  std::cout << "----Fromm----" << std::endl;
  fro.iterate("fromm", 4.0);
  fro.save_data("fromm.txt");

  simulation mimo(0.8, 400);
  std::cout << "----MinMod----" << std::endl;
  mimo.iterate("minmod", 4.0);
  mimo.save_data("minmod.txt");

  simulation sb(0.8, 400);
  std::cout << "----SuperBee----" << std::endl;
  sb.iterate("superbee", 4.0);
  sb.save_data("sb.txt");

  simulation mc(0.8, 400);
  std::cout << "----MC----" << std::endl;
  mc.iterate("mc", 4.0);
  mc.save_data("mc.txt");

  simulation vl(0.8, 400);
  std::cout << "----van-Leer----" << std::endl;
  vl.iterate("van_leer", 4.0);
  vl.save_data("vL.txt");
}