#include "RTau3pi.hpp"
#include <iostream>
#include <random>
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include "RLorentz.hpp"
#include "RParticleList.hpp"
#include "RParticle.hpp"
#include "RSO3.hpp"
const double pi = boost::math::constants::pi<double>();

RTau3pi::RTau3pi ()
{
  is_m3pi_fixed = false;
  init_random_generator ();
  init_masses ();
}

RTau3pi::RTau3pi (double arg_M3pi)
{
  m3pi = arg_M3pi;
  is_m3pi_fixed = true;
  init_random_generator ();
  init_masses();
}

void RTau3pi::init_random_generator ()
{
  std::random_device rd;
  gen.seed (rd());
}

void RTau3pi::init_masses ()
{
  RVector dummy;
  RParticle pi ("pi", dummy, dummy);
  RParticle nutau ("nutau", dummy, dummy);
  RParticle tau ("tau", dummy, dummy);
  mtau = tau.mass();
  mpi = pi.mass();
  mnu = nutau.mass();
}

void RTau3pi::init_random_generator (int seed)
{
  gen.seed (seed);
}

double RTau3pi::genFlat (double min, double max)
{
  if (min > max)
  {
    double tmp=max;
    max=min; min=max;
    std::cerr << "minimax" << " " << min << " " << max<<std::endl;
  }
  std::uniform_real_distribution <> distr (min, max);
  return distr (gen);
}

double RTau3pi::genExp (double lambda)
{
  if (lambda < 0)
    lambda = - lambda;
  std::exponential_distribution <> distr (lambda);
  return distr (gen);
}

double RTau3pi::sqr (double x) {return x*x;}

double RTau3pi::px (double e1, double e2, double p3, double m, int i)
{
  double sign =1.;
  if (i%2==0)
    sign=-1.;
  if (p3!=0)
    return -(p3/2. + sign /2. * (e1*e1-e2*e2)/p3);
  else
    if (sign <0)
      return -sqrt (e2*e2-m*m);
    else
      return sqrt (e1*e1-m*m);
}

bool RTau3pi::p1xmorep1 (double e1, double e2, double m3pi, double m)
{
  if (sqr(m3pi-e1-e2)-m*m<0)
    return true;
  double p3 = sqrt(sqr(m3pi-e1-e2)-m*m);
  return 2*p3*sqrt (e1*e1-m*m) < p3*p3+e1*e1-e2*e2;
}

RParticleList RTau3pi::genDecay (const RVector & ptau, const RVector & xtau)
{
  genTau (ptau, xtau);
  RLorentz P3pi = genNeutrino ();
  gen3pi (P3pi);
  return plist;
}

void RTau3pi::genTau (const RVector &ptau, const RVector &xtau)
{
  RParticle tau_m ("tau", ptau, xtau);
  mtau = tau_m.mass();
  Ptau = tau_m.getP(); 
  double tauct = tau_m.getCTau ();
  double beta = Ptau.beta ();
  double gamma = Ptau.gamma ();
  double length = genExp (-beta*gamma*tauct);
  Xtau = xtau+ptau * (length / ptau.length());
  tau_m.setX (Xtau);
  plist.add (tau_m);
}

RLorentz RTau3pi::genNeutrino ()
{
  //TODO make physical correct generation
  //calc neutrino momentum in tau rest frame
  RVector Pneutrino (0,0,0);
  RParticle nu ("nutau", Pneutrino, Xtau);
  if (not is_m3pi_fixed)
  {
    m3pi = genFlat (3*mpi, mtau-mnu);
  }
  //gen Neutrino
  double nu_phi = genFlat (0, 2*pi);
  double nu_costh = genFlat (0,1.);
  double nu_th = acos (nu_costh);
  double e_nu = (sqr(mtau)+sqr(nu.mass())-sqr(m3pi))/2./mtau;
  double p_nu = sqrt (sqr (e_nu) - sqr (nu.mass()));
  Pneutrino = RVector (p_nu * cos (nu_phi) * sin (nu_th),
    p_nu * sin (nu_phi) * sin (nu_th),
    p_nu * cos (nu_th));
  nu.setP (Pneutrino);
  //3 pi lorentz vector in tau rest frame
  RLorentz P3pi = RLorentz (mtau,0,0,0)-nu.getP();
  nu.boost (Ptau);
  plist.add (nu);
  return P3pi;
}

void RTau3pi::gen3pi (const RLorentz & P3pi)
{
  RVector Ppi1, Ppi2, Ppi3;
  RParticle pi1 ("pi", Ppi1,Xtau), pi2 ("pi", Ppi2, Xtau), pi3 ("pi", Ppi3,
    Xtau);
  pi1.chargeConjugate();
  pi3.chargeConjugate();
  //Neutrino generated. some kinematics to plot histogramms
  //through e1 and e2, fix a1 meson mass, a1 meson rest frame
  double a1_mass = m3pi;
  double E1=2*a1_mass;
  double E2=2*a1_mass;
  double m = pi1.mass();
  double ngen = 0;
  do
  {
    E1 = genFlat (pi1.mass(),a1_mass-2*pi1.mass());
    E2 = genFlat (pi1.mass(),a1_mass-2*pi1.mass());
    ngen = ngen+1;
  }
  while (p1xmorep1 (E1,E2,a1_mass,m) or p1xmorep1 (E2,E1,a1_mass,m) or (E1+E2>a1_mass-m));
  double E3 = a1_mass - E1 - E2;
  RVector p3 (sqrt(sqr(E3)-sqr(pi1.mass())),0,0);
  double p3x=p3.length();
  double p1x = px (E1,E2,p3x,m, 1);
  double p2x = px (E1,E2,p3x,m,2);
  double p1y= -sqrt (E1*E1-m*m-p1x*p1x);
  double p2y= sqrt (E2*E2-m*m-p2x*p2x);
  RVector p1 (p1x, p1y, 0);
  RVector p2 (p2x, p2y, 0);
  //euler transform
  double alpha=genFlat (0,2*pi);
  double gamma=genFlat(0,2*pi);
  double cosbeta = genFlat (0,1);
  double beta = acos (cosbeta);
  RSO3 euler;
  euler.EulerTransform (alpha, beta, gamma);
  p1 = euler*p1;
  p2 = euler*p2;
  p3 = euler*p3;
  pi1.setP (p1);
  pi2.setP (p2);
  pi3.setP (p3);
  //boost to tau rest frame system (alongside a1)
  pi1.boost (P3pi);
  pi2.boost (P3pi);
  pi3.boost (P3pi);
  //boost to "lab" rest frame (alongside tau)
  pi1.boost (Ptau);
  pi2.boost (Ptau);
  pi3.boost (Ptau);
  plist.add (pi1);
  plist.add (pi2);
  plist.add (pi3);
}

