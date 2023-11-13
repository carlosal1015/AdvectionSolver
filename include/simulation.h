#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include "fluxes.h"
using namespace std;

//declaration for class simulation
class simulation : fluxes {
    public:
        simulation (double sigma, int grid_len); //constructor
        void print_att();
        void iterate(string, double);
        void bord_con();
        void save_data(string);
};