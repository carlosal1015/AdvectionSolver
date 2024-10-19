#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

class fluxes {
public:
  int M;
  double Δt;
  double Δx;
  double σ;
  std::vector<double> u;
  std::vector<double> slope;
  std::vector<double> flux; // at the moment only used for mc, rest is
                            // calculated via slopes or directly
public:
  fluxes(int M, double Δt, double Δx, double σ); // constructor
  fluxes();

  void upwind(std::vector<double> u_new);
  void lax_wendroff(std::vector<double> u_new);
  void beam_warming(std::vector<double> u_new);
  void fromm(std::vector<double> u_new);
  void minmod(std::vector<double> u_new);
  void superbee(std::vector<double> u_new);
  void mc(std::vector<double> u_new);
  void van_leer(std::vector<double> u_new);
};
