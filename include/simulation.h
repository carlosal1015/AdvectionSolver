#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include "fluxes.h"
using namespace std;

// declaration for class simulation
class simulation : fluxes
{
public:
    simulation(double sigma, int grid_len); // default dist constructor
    simulation(double sigma, double xmin, double xmax, vector<double> initialDistribution); // custom dist constructor
    void print_att();
    void iterate(string, double);
    void save_data(string);
private:
    double xmin;
    void bord_con();
};