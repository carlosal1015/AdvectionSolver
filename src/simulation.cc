#include "simulation.hh"

// const double M_PI = std::atan(1.0)*4;
constexpr double PI = std::numbers::pi;

// constructor for class simulation
simulation::simulation(double σ, int grid_len) : fluxes()
{
  this->σ = σ;
  // choosing default computation domain of [0, 2]
  this->xmin = -1.0;
  this->Δx = 2.0 / double(grid_len);
  Δt = this->σ * this->Δx;
  this->M = grid_len + 4; // length of grid +2 borders on each side

  // initialize grid quantities
  this->u = std::vector<double>(this->M, 0.0);
  this->slope = std::vector<double>(this->M, 0.0);
  this->flux = std::vector<double>(this->M, 0.0);

  // set q(x, t=0)
  for (unsigned int i = 0; i < u.size(); i++) {
    double x = ((i - 2) * this->Δx - 1.0);
    if ((-2.0 / 3.0 < x) & (x < -1.0 / 3.0)) {
      this->u[i] = 1.0;
    }
    if (x > 0.0) {
      this->u[i] = 0.5 * sin(2.0 * PI * x);
    }
    // cout << i << " " << u[i] << endl;
  }
}

simulation::simulation(double σ, double xmin, double xmax,
                       std::vector<double> initialDistribution)
    : fluxes()
{
  // set simualtion and fluxes basic attributes
  this->xmin = xmin;
  this->σ = σ;
  this->Δx = (xmax - xmin) / double(initialDistribution.size() - 1);
  this->M =
      initialDistribution.size() + 4; // length of grid +2 borders on each side
  // get timestep
  Δt = this->σ * this->Δx;

  // set q(x, t=0)
  this->u = initialDistribution;
  u.insert(u.begin(), 2, 0.0);
  u.push_back(0.0);
  u.push_back(0.0);

  // initialize other grid quantities and fill ghost cells
  this->slope = std::vector<double>(this->M, 0.0);
  this->flux = std::vector<double>(this->M, 0.0);
  bord_con(); // fill ghost cells

  // print dist
  /*
  for (unsigned int i = 0; i < u.size(); i++)
  {
      cout << i << " " << u[i] << endl;
  }
  */
}

void simulation::print_att()
{
  // method to print relevant attributes of current class
  std::cout
      << "------------------------------------------\nAttributes of current "
         "simulation class are:\n";
  std::cout << "\nActive gridpoints:  " << M - 4 << std::endl;
  std::cout << "Δt:  " << Δt << std::endl;
  std::cout << "Δx:  " << Δx << std::endl;
  /*cout << "u:  [" ;
  for (auto & it : u){
      cout << it << ", ";
  }
  cout << "]" << endl;*/
}

void simulation::iterate(std::string iterator, double t_end)
{
  double t = 0.0;
  std::vector<double> u_new = u;
  bool is_known_iterator = true;
  std::map<std::string, void (simulation::*)(std::vector<double>)> schemes = {
      {"upwind", &simulation::upwind},
      {"lax_wendroff", &simulation::lax_wendroff},
      {"beam_warming", &simulation::beam_warming},
      {"fromm", &simulation::fromm},
      {"minmod", &simulation::minmod},
      {"superbee", &simulation::superbee},
      {"mc", &simulation::mc},
      {"van_leer", &simulation::van_leer}};
  std::map<std::string, void (simulation::*)(std::vector<double>)>::iterator it;
  it = schemes.find(iterator);
  // declare pointer-to-member-function to avoid having to put the iterator
  // cases inside the loop
  void (simulation::*funcptr)(std::vector<double>) = nullptr;
  if (it != schemes.end()) // searched key exists
  {
    funcptr = it->second;
  }
  else // key doesn't exist
  {
    std::cout << "Unknown iterator!";
    is_known_iterator = false;
  }

  // loop over all timesteps
  if (is_known_iterator) {
    while (t < t_end) {
      // run the declared iterator via pointer to member function
      (this->*funcptr)(u_new);
      // set border conditions
      bord_con();
      // update timestep
      t += Δt;
    }
  }
}

void simulation::save_data(std::string file_name)
{
  // method to save M, σ, as well as x and u data of current timestep in txt
  // file
  std::cout << "Saving data..." << std::endl;
  std::ofstream myfile;
  myfile.open(file_name);
  myfile << M << ", " << σ << "\n";
  for (size_t i = 2; i < u.size() - 1; ++i) {
    myfile << xmin + Δx * (i - 2) << ", " << u[i] << "\n";
  }
  myfile.close();
  std::cout << "success!" << std::endl;
}

void simulation::bord_con()
{
  // method to set periodic boundry conditions
  u[1] = u[M - 3];
  u[0] = u[M - 4];
  u[M - 1] = u[3];
  u[M - 2] = u[2];
}
