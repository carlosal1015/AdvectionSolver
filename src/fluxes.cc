#include "fluxes.hh"

fluxes::fluxes(int M, double Δt, double Δx, double σ)
{
  this->M = M;
  this->Δt = Δt;
  this->Δx = Δx;
  this->σ = σ;
}

fluxes::fluxes() {}

void fluxes::upwind(std::vector<double> u_new)
{
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (u[i] - u[i - 1]);
  }
  u = u_new;
}

void fluxes::lax_wendroff(std::vector<double> u_new)
{
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ / 2.0 * (u[i + 1] - u[i - 1]) +
               std::pow(σ, 2.0) / 2.0 * (u[i + 1] - 2.0 * u[i] + u[i - 1]);
  }
  u = u_new;
}

void fluxes::beam_warming(std::vector<double> u_new)
{
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (u[i] - u[i - 1]) -
               σ / 2.0 * ((u[i] - 2.0 * u[i - 1] + u[i - 2]) / Δx) *
                   (Δx - Δt);
  }
  u = u_new;
}

void fluxes::fromm(std::vector<double> u_new)
{
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (u[i] - u[i - 1]) -
               σ / 2.0 *
                   ((u[i + 1] - u[i - 1]) / (2.0 * Δx) -
                    (u[i] - u[i - 2]) / (2.0 * Δx)) *
                   (Δx - Δt);
  }
  u = u_new;
}

void fluxes::minmod(std::vector<double> u_new)
{
  // implemented as slope limiter
  // calculate slope
  for (int i = 1; i < M - 2; i++) {
    double num1 = (u[i] - u[i - 1]) / Δx;
    double num2 = (u[i + 1] - u[i]) / Δx;
    if ((num1 * num2) > 0.0) {
      if (std::abs(num1) < std::abs(num2)) {
        slope[i] = num1;
      }
      else {
        slope[i] = num2;
      }
    }
    else {
      slope[i] = 0;
    }
  }
  // now use slope to update q
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (u[i] - u[i - 1]) -
               σ / 2.0 * (slope[i] - slope[i - 1]) * (Δx - Δt);
  }
  u = u_new;
}

void fluxes::superbee(std::vector<double> u_new)
{
  // implemented as slope limiter
  // calculate slope
  for (int i = 1; i < M - 2; i++) {
    double num1 = (u[i + 1] - u[i]) / Δx;
    double num2 = (u[i] - u[i - 1]) / Δx;
    double s1 = 0.0;
    double s2 = 0.0;
    // calculate minmods s1 and s2
    if ((num1 * num2) > 0.0) {
      if (std::abs(num1) < std::abs(2.0 * num2)) {
        s1 = num1;
      }
      else {
        s1 = 2.0 * num2;
      }
      if (std::abs(2.0 * num1) < std::abs(num2)) {
        s2 = 2.0 * num1;
      }
      else {
        s2 = num2;
      }
    }
    // calculate maxmod of s1 and s2
    slope[i] = 0.0;
    if ((s1 * s2) > 0) {
      if (std::abs(s1) < std::abs(s2)) {
        slope[i] = s2;
      }
      else {
        slope[i] = s1;
      }
    }
  }
  // now use slope to update q
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (u[i] - u[i - 1]) -
               σ / 2.0 * (slope[i] - slope[i - 1]) * (Δx - Δt);
  }
  u = u_new;
}

void fluxes::mc(std::vector<double> u_new)
{
  // implemented as flux limiter
  // calculate flux: index i of flux vector contains flux at i-0.5
  for (int i = 2; i < M - 1; i++) {
    double r = (u[i - 1] - u[i - 2]) /
               (u[i] - u[i - 1] + 1E-16); //+1E-16 to avoid div0
    double phi = std::max({0.0, std::min({(1 + r) / 2.0, 2.0, 2.0 * r})});
    flux[i] = u[i - 1] + 0.5 * (1 - σ) * (u[i] - u[i - 1]) * phi;
  }
  // now use flux to update q
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (flux[i + 1] - flux[i]);
  }
  u = u_new;
}

void fluxes::van_leer(std::vector<double> u_new)
{
  // implemented as flux limiter
  // calculate flux:
  for (int i = 2; i < M - 1; i++) {
    double r = (u[i - 1] - u[i - 2]) /
               (u[i] - u[i - 1] + 1E-16); //+1E-16 to avoid div0
    double phi = (r + std::abs(r)) / (1 + std::abs(r));
    flux[i] = u[i - 1] + 0.5 * (1 - σ) * (u[i] - u[i - 1]) * phi;
  }
  // now use flux to update q
  for (int i = 2; i < M - 2; i++) {
    u_new[i] = u[i] - σ * (flux[i + 1] - flux[i]);
  }
  u = u_new;
}
