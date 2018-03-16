#pragma once
#include "RVector.hpp"

class RLorentz
{
  private:
    double fx, fy, fz, ft;
  public:
    RLorentz (double t, double x, double y, double z)
      {ft=t; fx=x; fy=y; fz=z;};
    RLorentz (double t, const RVector & vector3)
      {ft = t; vector3.getXYZ (fx, fy, fz);};
    RLorentz (const RVector & vector3, double m);//make vector with known mass
    RVector getVector () const {return RVector (fx, fy, fz);};
    double getT () const { return ft;};
}
