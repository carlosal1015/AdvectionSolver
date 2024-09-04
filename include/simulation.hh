#pragma once

#include "fluxes.hh"
#include <fstream>
#include <iostream>
#include <map>
#include <numbers>
#include <string>

// declaration for class simulation
class simulation : fluxes {
public:
  simulation(double sigma, int grid_len); // default dist constructor
  simulation(
      double sigma, double xmin, double xmax,
      std::vector<double> initialDistribution); // custom dist constructor
  void print_att();
  void iterate(std::string, double);
  void save_data(std::string);

private:
  double xmin;
  void bord_con();
};
