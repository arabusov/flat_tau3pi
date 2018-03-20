#include "RLorentz.hpp"
#include "RVector.hpp"
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#define debug 1
double RLorentz::getM () const
{
  double mm = (ft*ft - fx*fx - fy*fy - fz*fz); 
  if (mm>=0)
    return sqrt (mm);
  else
    return -mm;
}

double RLorentz::gamma () const
{
  return E()/m();
}

double RLorentz::beta () const
{
  return sqrt(1-1/gamma()/gamma());
}

void RLorentz::boost (const RLorentz & kuda, int sign)
{
  double beta = sign * kuda.beta ();
  double gamma = kuda.gamma ();
  RVector direction = kuda.getVector ();
  RVector longiProj = vector().proj (direction);
  RVector transProj = vector () - longiProj;
  double length = longiProj.length();
  double ftt = gamma*ft + beta*gamma*length;
  longiProj = longiProj * (1./length);
  length = gamma*length + beta*gamma*ft;
  longiProj = longiProj * length;
  RVector sum = longiProj + transProj;
  sum.getXYZ (fx, fy, fz);
  ft = ftt;
  return;
}

void RLorentz::LorentzTransform (const RLorentz & restFrame)
{
  boost (restFrame, -1); //-1 : sign before beta
}

void RLorentz::LorentzInverseTransform (const RLorentz & boostLVector)
{
  boost (boostLVector, 1);
}

RLorentz operator+ (const RLorentz& left, const RLorentz& right)
{
  RLorentz res (
    left.t()+right.t(),   
    left.x()+right.x(),   
    left.y()+right.y(),   
    left.z()+right.z());
  return res;
}
  
RLorentz operator- (const RLorentz& left, const RLorentz& right)
{
  return left+(-1.)*right;
}

double operator* (const RLorentz& left, const RLorentz& right)
{
  double res =
    left.t()*right.t()-
    left.x()*right.x()-   
    left.y()*right.y()-   
    left.z()*right.z();
  return res;
}

RLorentz operator* (const RLorentz& left, const double& right)
{
  RLorentz res (
    left.t()*right, 
    left.x()*right,   
    left.y()*right,   
    left.z()*right);
  return res;
}

RLorentz operator* (const double & left, const RLorentz & right)
{
  return right*left;
}

std::string RLorentz::str () const
{
  std::stringstream ss;
  ss << ft<<" " <<fx << " " << fy << " " << fz << " ";
  return ss.str();
}

