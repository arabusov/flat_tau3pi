/*
 * Simple generator of tau decay to 3 pi nu without hadron dynamics
 * (so-called flat MC)
 * All calculations in tau rest frame
 */
#include <random>
#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include "RLorentz.hpp"
#include "RParticleList.hpp"
#include "RParticle.hpp"

const double pi = boost::math::constants::pi<double>();
double genFlat (double min=-1., double max=1.)
{
  if (min > max)
  {
    double tmp=max;
    max=min; min=max;
  }
  std::random_device rd; //initial seed
  std::mt19937 gen (rd());
  std::uniform_real_distribution <> distr (min, max);
  return distr (gen);
}

//RParticleList genDecay (const RVector & Ptau, const RVector & Xtau)
void genDecay (const RVector & Ptau, const RVector & Xtau)
{
  //RParticleList plist;
  RParticle tau_m ("tau", Ptau, Xtau);
  double tau_mass = tau_m.mass();
  //plist.add (tau_m);
  //TODO make physical correct generation
  //calc neutrino momentum in tau rest frame
  double m3pi = genFlat (0, tau_m.mass());
  double nu_phi = genFlat (0, 2*pi);
  double nu_th = genFlat (0,pi);
  double p_nu = pow (tau_mass*tau_mass - m3pi*m3pi, 0.5); 
  RVector Pneutrino (p_nu * cos (nu_phi) * sin (nu_th),
    p_nu * sin (nu_phi) * sin (nu_th),
    p_nu * cos (nu_th));
  RParticle nu ("nutau", Pneutrino, Xtau);
  nu.boost (tau_m.getP()); //boost tau to lab
  //plist.add (nu);

}

int main (int argc, char ** argv)
{
  return 0;

}

