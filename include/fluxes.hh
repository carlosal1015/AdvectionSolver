#pragma once

#include <algorithm>
#include <vector>
#include <cmath>

class fluxes {
public:
  int M;
  double delta_t;
  double delta_x;
  double sigma;
  std::vector<double> u;
  std::vector<double> slope;
  std::vector<double> flux; // at the moment only used for mc, rest is
                            // calculated via slopes or directly
public:
  fluxes(int M, double delta_t, double delta_x, double sigma); // constructor
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
