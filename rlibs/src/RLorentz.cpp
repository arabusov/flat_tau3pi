#include "RLorentz.hpp"
#include "RVector.hpp"
#include <cmath>

double RLorentz::getM () const
{
  return sqrt(ft*ft - fx*fx - fy*fy - fz*fz); 
}

double RLorentz::gamma () const
{
  return E()/m();
}

double RLorentz::beta () const
{
  return sqrt(1-1/gamma()/gamma());
}

void RLorentz::boost (const RLorentz & kuda)
{
  double beta = kuda.beta ();
  double gamma = kuda.gamma ();
  RVector direction = kuda.getVector ();
  RVector longiProj = vector().proj (direction);
  RVector transProj = vector () - longiProj;

