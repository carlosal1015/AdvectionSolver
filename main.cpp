#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//A program to solve the 1D linear advection equation with different methods and slope/flux limiters


//declaration for class simulation
class simulation {
    public:
        int M;
        double delta_t;
        double delta_x;
        double sigma;
        vector <double> u;
        vector <double> slope;
        vector <double> flux; //at the moment only used for mc, rest is calculated via slopes or directly
    public:
        simulation (double, int); //constructor
        void print_att();
       
        void iterate(string, double);
        void upwind(vector<double>);
        void lax_wendroff(vector<double>);
        void beam_warming(vector<double>);
        void fromm(vector<double>);
        void minmod(vector<double>);
        void superbee(vector<double>);
        void mc(vector<double>);
        void van_leer(vector<double>);
        void bord_con();
        void save_data(string);

};


//constructor for class simulation
simulation::simulation(double sigma, int grid_len)
{
    this->sigma = sigma;
    delta_x = 2.0/double(grid_len);
    delta_t = sigma*delta_x;
    M = grid_len + 4; //length of grid +2 borders on each side

    //initialize grid quantities
    u = vector<double> (M, 0.0);
    slope = vector<double> (M, 0.0);
    flux = vector<double> (M, 0.0);

    //set q(x, t=0)
    for (unsigned int i = 0; i < u.size(); i++){
        double x = ((i-2)*delta_x-1.0);
        if ((-2.0/3.0 < x) & (x < -1.0/3.0)){
            u[i] = 1.0;
        }
        if (x>0.0){
            u[i] = 0.5*sin(2.0*M_PI*x);
        }
        //cout << i << " " << u[i] << endl;
    }
}


void simulation::print_att()
{
    //method to print relevant attributes of current class
    cout << "------------------------------------------\nAttributes of current simulation class are:\n";
    cout << "\nActive gridpoints:  " << M-4 << endl;
    cout << "delta_t:  " << delta_t << endl;
    cout << "delta_x:  " << delta_x << endl;
    /*cout << "u:  [" ;
    for (auto & it : u){
        cout << it << ", ";
    }
    cout << "]" << endl;*/
    
}


void simulation::iterate(string iterator, double t_end)
{
    double t = 0.0;
    vector<double> u_new = u;
    bool is_known_iterator = true;
    //declare pointer-to-member-function to avoid having to put the iterator cases inside the loop
    void (simulation::*funcptr)(vector<double>) = nullptr;
    if (iterator == "upwind"){
        funcptr = &simulation::upwind;
    }
    else if (iterator == "lax_wendroff")
    {
        funcptr = &simulation::lax_wendroff;
    }
    else if (iterator == "beam_warming")
    {
        funcptr = &simulation::beam_warming;
    }
    else if (iterator == "fromm")
    {
        funcptr = &simulation::fromm;
    }
    else if (iterator == "minmod")
    {
        funcptr = &simulation::minmod;
    }
    else if (iterator == "superbee")
    {
        funcptr = &simulation::superbee;
    }
    else if (iterator == "mc")
    {
        funcptr = &simulation::mc;
    }
        else if (iterator == "van_leer")
    {
        funcptr = &simulation::van_leer;
    }
    else{
        cout << "Unknown iterator!";
        is_known_iterator = false;
    }
    
    //loop over all timesteps
    if (is_known_iterator){
        while (t < t_end){
            //run the declared iterator via pointer to member function
            (this->*funcptr)(u_new);
            //set border conditions
            bord_con();
            //update timestep
            t += delta_t;
        }
    }

}


void simulation::save_data(string file_name)
{
    //method to save M, sigma, as well as x and u data of current timestep in txt file
    cout << "Saving data..." << endl;
    ofstream myfile;
    myfile.open(file_name);
    myfile << M << ", " << sigma << "\n";
    for (size_t i = 2; i<u.size()-1; ++i){
        myfile << -1.0+delta_x*(i-2) << ", " << u[i] << "\n";
    }
    myfile.close();
    cout << "success!" << endl;
}


void simulation::upwind(vector<double> u_new)
{
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(u[i]-u[i-1]);
    }
    u = u_new;
}


void simulation::lax_wendroff(vector<double> u_new)
{
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma/2.0*(u[i+1]-u[i-1])+pow(sigma, 2.0)/2.0*(u[i+1]-2.0*u[i]+u[i-1]);
    }
    u = u_new;
}


void simulation::beam_warming(vector<double> u_new)
{
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(u[i]-u[i-1]) - sigma/2.0 * ((u[i]-2.0*u[i-1]+u[i-2])/delta_x)*(delta_x - delta_t);
    }
    u = u_new;
}


void simulation::fromm(vector<double> u_new)
{
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(u[i]-u[i-1]) - sigma/2.0 * ((u[i+1]-u[i-1])/(2.0*delta_x) - (u[i]-u[i-2])/(2.0*delta_x))*(delta_x - delta_t);
    }
    u = u_new;
}


void simulation::minmod(vector<double> u_new)
{
    //implemented as slope limiter
    //calculate slope
    for (int i = 1; i<M-2; i++){
        double num1 = (u[i]-u[i-1])/delta_x;
        double num2 = (u[i+1]-u[i])/delta_x;
        if ((num1*num2) > 0.0){
            if (abs(num1) < abs(num2)){
                slope[i] = num1;
            }
            else{
                slope[i] = num2;
            }
        }
        else{
            slope[i] = 0;
        }
    }
    //now use slope to update q
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(u[i]-u[i-1]) - sigma/2.0 * (slope[i] - slope[i-1])*(delta_x - delta_t);
    }
    u = u_new;
}


void simulation::superbee(vector<double> u_new)
{
    //implemented as slope limiter
    //calculate slope
    for (int i = 1; i<M-2; i++){
        double num1 = (u[i+1]-u[i])/delta_x;
        double num2 = (u[i]-u[i-1])/delta_x;
        double s1 = 0.0;
        double s2 = 0.0;
        //calculate minmods s1 and s2
        if ((num1*num2) > 0.0){
            if (abs(num1) < abs(2.0*num2)){
                s1 = num1;
            }
            else{
                s1 = 2.0*num2;
            }
            if (abs(2.0*num1) < abs(num2)){
                s2 = 2.0*num1;
            }
            else{
                s2 = num2;
            }
        }
        //calculate maxmod of s1 and s2
        slope[i] = 0.0;
        if ((s1*s2) > 0){
            if (abs(s1)<abs(s2)){
                slope[i] = s2;
            }
            else{
                slope[i] = s1;
            }
        }
    }
    //now use slope to update q
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(u[i]-u[i-1]) - sigma/2.0 * (slope[i] - slope[i-1])*(delta_x - delta_t);
    }
    u = u_new;
}


void simulation::mc(vector<double> u_new)
{
    //implemented as flux limiter
    //calculate flux: index i of flux vector contains flux at i-0.5
    for (int i = 2; i<M-1; i++){
        double r = (u[i-1]-u[i-2])/(u[i]-u[i-1]+1E-16); //+1E-16 to avoid div0
        double phi = max({0.0, min({(1+r)/2.0, 2.0, 2.0*r})});
        flux[i] = u[i-1] + 0.5*(1-sigma)*(u[i]-u[i-1])*phi;
    }
    //now use flux to update q
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(flux[i+1]-flux[i]);
    }
    u = u_new;
}


void simulation::van_leer(vector<double> u_new)
{
    //implemented as flux limiter
    //calculate flux:
    for (int i = 2; i<M-1; i++){
        double r = (u[i-1]-u[i-2])/(u[i]-u[i-1]+1E-16);//+1E-16 to avoid div0
        double phi = (r+abs(r))/(1+abs(r));
        flux[i] = u[i-1] + 0.5*(1-sigma)*(u[i]-u[i-1])*phi;
    }
    //now use flux to update q
    for (int i = 2; i<M-2; i++){
        u_new[i] = u[i] - sigma*(flux[i+1]-flux[i]);
    }
    u = u_new;
}


void simulation::bord_con()
{
    //method to set periodic boundry conditions
    u[1] = u[M-3];
    u[0] = u[M-4];
    u[M-1] = u[3];
    u[M-2] = u[2];
}


int main()
{
    simulation Ana(0.8, 400);
    cout << "Generation analytical solution!" << endl;
    Ana.save_data("analytical.txt");

    simulation Up(0.8, 400);
    cout << "----Upwind----" << endl;
    Up.iterate("upwind", 4.0);
    Up.save_data("upwind.txt");

    simulation Lax(0.8, 400);
    cout << "----Lax-Wendroff----" << endl;
    Lax.iterate("lax_wendroff", 4.0);
    Lax.save_data("lax.txt");

    simulation beam(0.8, 400);
    cout << "----Beam-Warming----" << endl;
    beam.iterate("beam_warming", 4.0);
    beam.save_data("beam.txt");

    simulation fro(0.8, 400);
    cout << "----Fromm----" << endl;
    fro.iterate("fromm", 4.0);
    fro.save_data("fromm.txt");

    simulation mimo(0.8, 400);
    cout << "----MinMod----" << endl;
    mimo.iterate("minmod", 4.0);
    mimo.save_data("minmod.txt");

    simulation sb(0.8, 400);
    cout << "----SuperBee----" << endl;
    sb.iterate("superbee", 4.0);
    sb.save_data("sb.txt");

    simulation mc_(0.8, 400);
    cout << "----MC----" << endl;
    mc_.iterate("mc", 4.0);
    mc_.save_data("mc.txt");

    simulation vl(0.8, 400);
    cout << "----van-Leer----" << endl;
    vl.iterate("van_leer", 4.0);
    vl.save_data("vL.txt");

}