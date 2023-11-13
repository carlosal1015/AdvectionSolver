#include "simulation.h"

// constructor for class simulation
simulation::simulation(double sigma, int grid_len) : fluxes()
{
    this->sigma = sigma;
    this->delta_x = 2.0 / double(grid_len);
    delta_t = this->sigma * this->delta_x;
    this->M = grid_len + 4; // length of grid +2 borders on each side

    // initialize grid quantities
    this->u = vector<double>(this->M, 0.0);
    this->slope = vector<double>(this->M, 0.0);
    this->flux = vector<double>(this->M, 0.0);

    // set q(x, t=0)
    for (unsigned int i = 0; i < u.size(); i++)
    {
        double x = ((i - 2) * this->delta_x - 1.0);
        if ((-2.0 / 3.0 < x) & (x < -1.0 / 3.0))
        {
            this->u[i] = 1.0;
        }
        if (x > 0.0)
        {
            this->u[i] = 0.5 * sin(2.0 * M_PI * x);
        }
        // cout << i << " " << u[i] << endl;
    }
}

void simulation::print_att()
{
    // method to print relevant attributes of current class
    cout << "------------------------------------------\nAttributes of current simulation class are:\n";
    cout << "\nActive gridpoints:  " << M - 4 << endl;
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
    // declare pointer-to-member-function to avoid having to put the iterator cases inside the loop
    void (simulation::*funcptr)(vector<double>) = nullptr;
    if (iterator == "upwind")
    {
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
    else
    {
        cout << "Unknown iterator!";
        is_known_iterator = false;
    }

    // loop over all timesteps
    if (is_known_iterator)
    {
        while (t < t_end)
        {
            // run the declared iterator via pointer to member function
            (this->*funcptr)(u_new);
            // set border conditions
            bord_con();
            // update timestep
            t += delta_t;
        }
    }
}

void simulation::save_data(string file_name)
{
    // method to save M, sigma, as well as x and u data of current timestep in txt file
    cout << "Saving data..." << endl;
    ofstream myfile;
    myfile.open(file_name);
    myfile << M << ", " << sigma << "\n";
    for (size_t i = 2; i < u.size() - 1; ++i)
    {
        myfile << -1.0 + delta_x * (i - 2) << ", " << u[i] << "\n";
    }
    myfile.close();
    cout << "success!" << endl;
}

void simulation::bord_con()
{
    // method to set periodic boundry conditions
    u[1] = u[M - 3];
    u[0] = u[M - 4];
    u[M - 1] = u[3];
    u[M - 2] = u[2];
}
