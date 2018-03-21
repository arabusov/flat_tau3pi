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
#include "RSO3.hpp"

const double pi = boost::math::constants::pi<double>();
double genFlat (std::random_device & rd, double min=-1., double max=1.)
{
  if (min > max)
  {
    double tmp=max;
    max=min; min=max;
    std::cerr << "minimax" << " " << min << " " << max<<std::endl;
  }
//  std::mt19937 gen (rd());
  std::uniform_real_distribution <> distr (min, max);
  return distr (rd);
}
double sqr (double x) {return x*x;}

double px (double e1, double e2, double p3, int i=1)
{
  double sign = i%2==0 ? -1.: 1.;
  return p3/2. + sign /2. * (e1*e1-e2*e2);
}

double py (double e1, double e2, double p3, double m, int i=1)
{
  double sign = i%2==0 ? -1.: 1.;
  return sign*((e1*e1 + e2*e2 -p3*p3)/2. - sqr(e1*e1-e2*e2)/4./p3/p3);
}
//RParticleList genDecay (const RVector & Ptau, const RVector & Xtau)
RParticleList genDecay (std::random_device & rd, RVector & Ptau, RVector & Xtau)
{
  RParticleList plist;
  RParticle tau_m ("tau", Ptau, Xtau);
  double tau_mass = tau_m.mass();
  plist.add (tau_m);
  //TODO make physical correct generation
  //calc neutrino momentum in tau rest frame
  RVector Pneutrino (0,0,0), Ppi1, Ppi2, Ppi3;
  RParticle nu ("nutau", Pneutrino, Xtau);
  RParticle pi1 ("pi", Ppi1,Xtau), pi2 ("pi", Ppi2, Xtau), pi3 ("pi", Ppi3,
    Xtau);
  pi3.chargeConjugate();
  double m3pi = genFlat (rd, 3*pi1.mass(), tau_m.mass()-nu.mass());
  //gen Neutrino
  double nu_phi = genFlat (rd,0, 2*pi);
  double nu_costh = genFlat (rd,-1.,1.);
  double nu_th = acos (nu_costh);
  double e_nu = (sqr(tau_m.mass())+sqr(nu.mass())-sqr(m3pi))/2./tau_m.mass();
  double p_nu = sqrt (sqr (e_nu) - sqr (nu.mass()));
  Pneutrino = RVector (p_nu * cos (nu_phi) * sin (nu_th),
    p_nu * sin (nu_phi) * sin (nu_th),
    p_nu * cos (nu_th));
  nu.setP (Pneutrino);
  nu.boost (tau_m.getP()); //boost from tau to "lab" system
  plist.add (nu);
  //Neutrino generated. some kinematics to plot histogramms
  //nu.LorentzTransform (tau_m.getP());
  //blah blah
  //through e1 and e2, fix a1 meson mass, a1 meson rest frame
  double a1_mass = 1.;
  double E1=a1_mass;
  double E2=a1_mass;
  double ngen = 0;
  while ((E1+E2 )>( a1_mass - pi1.mass()))
  {
    E1 = genFlat (rd, pi1.mass(),a1_mass-2*pi1.mass());
    E2 = genFlat (rd, pi1.mass(),a1_mass-2*pi1.mass());
    ngen = ngen+1;
  }
  double E3 = a1_mass - E1 - E2;
  RVector p3 (sqrt(sqr(E3)-sqr(pi1.mass())),0,0);
  std::cout << p3.length() << " ";
  double p3x=p3.length();
  double p1x = px (E1,E2,p3x,1);
  double p2x = px (E1,E2,p3x,2);
  double p1y = py (E1,E2, p3x, pi1.mass(),1);
  double p2y = py (E1,E2, p3x, pi2.mass(),2);
  RVector p1 (-p1x, p1y, 0);
  RVector p2 (-p2x, p2y, 0);
  std::cout << E1*E1 - p1*p1 << " ";
  std::cout << E2*E2 - p2*p2 << " ";
  std::cout << sqrt(E3*E3 - p3*p3) << " ";
  //euler transform
  double alpha=genFlat (rd,0,2*pi);
  double gamma=genFlat(rd,0,2*pi);
  double cosbeta = genFlat (rd,-1,1);
  double beta = acos (cosbeta);
  RSO3 euler;
  euler.EulerTransform (alpha, beta, gamma);
  p3 = euler*p3;
  //boost to tau rest frame system (alongside a1)
  //boost to "lab" rest frame (alongside tau)
  std::cout << std::endl;
  return plist;
}

void genEvent (std::random_device & rd)
{
  double r = genFlat (rd, 1,2);
  double theta = acos(sqrt (r-1));
  double phi = genFlat (rd, 0,2*pi);
  double P=1.;
  RVector Ptau (P*sin(theta)*cos(phi),P*sin(theta)*sin(phi),P*cos(theta));
  RVector Xtau (0,0,0);
  RParticleList plist = genDecay (rd, Ptau, Xtau);
}

int main (int argc, char ** argv)
{
  std::random_device rd; //initial seed
  for (unsigned int i = 0; i < 100000; i++)
  {
    genEvent (rd);   
  }
  return 0;
}

