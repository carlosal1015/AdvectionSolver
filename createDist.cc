#include <fstream>
#include <iostream>
#include <vector>

/*This script can create a custom discrete distribution from a given interval
and given function. More complex distributions may require if else cases to
switch between different generation functions in function().
*/

//----- TO MODIFY ------
// Globals
double X_MIN = 0.0;
double X_MAX = 2.0;
double DELTA = 0.01;
std::string OUT_FILE_PATH = "customDist.txt";

// generation function
inline double function(double x) { return 10.0 * x; }
//----- xxxxxxxxx ------

// creates a vector of doubles with lenght int((min-max)/delta)
// excludes max if (max-min)%delta != 0
std::vector<double> linspace(double min, double max, double delta)
{
  int nSteps = int((max - min) / delta);
  std::vector<double> x(nSteps + 1);
  for (size_t i = 0; i < nSteps + 1; i++) {
    x.at(i) = min + i * delta;
  }
  return x;
}

std::vector<double> makeDist(double xmin, double xmax, double delta)
{
  // generate linspace
  std::vector<double> x = linspace(xmin, xmax, delta);
  // set each element of x to f(x)
  for (auto &element : x) {
    element = function(element);
  }
  return x;
}

void printDist(std::vector<double> v)
{
  for (const auto &element : v) {
    std::cout << element << std::endl;
  }
}

void saveVec(std::vector<double> v, std::string filename)
{
  std::ofstream out;
  out.open(filename);
  if (out.is_open()) {
    std::cout << "Opened \'" << filename << "\' successfully" << std::endl;
    for (const auto &element : v) {
      out << element << " ";
    }
    out << std::endl;
  }
  else {
    std::cout << "File \'" << filename
              << "\' can't be opened\n Abort saving file";
  }
}

int main()
{
  std::vector<double> distribution = makeDist(X_MIN, X_MAX, DELTA);
  saveVec(distribution, OUT_FILE_PATH);
}