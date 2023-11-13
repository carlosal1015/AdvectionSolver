#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

class fluxes {
    public:
        int M;
        double delta_t;
        double delta_x;
        double sigma;
        vector <double> u;
        vector <double> slope;
        vector <double> flux; //at the moment only used for mc, rest is calculated via slopes or directly
    public:
        fluxes (int M, double delta_t, double delta_x, double sigma); //constructor
        fluxes();

        void upwind(vector<double> u_new);
        void lax_wendroff(vector<double> u_new);
        void beam_warming(vector<double> u_new);
        void fromm(vector<double> u_new);
        void minmod(vector<double> u_new);
        void superbee(vector<double> u_new);
        void mc(vector<double> u_new);
        void van_leer(vector<double> u_new);

};