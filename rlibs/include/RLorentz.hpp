#pragma once
#include "RVector.hpp"
#include <cmath>
#include <string>

class RLorentz
{
  private:
    double fx, fy, fz, ft;
  public:
    RLorentz () {fx=0; fy=0; fz=0; ft=0;};
    RLorentz (double t, double x, double y, double z)
      {ft=t; fx=x; fy=y; fz=z;};
    RLorentz (double t, const RVector & vector3)
      {ft = t; vector3.getXYZ (fx, fy, fz);};
    RLorentz (const RVector & vector3, double m);//make vector with known mass
    RVector getVector () const {return RVector (fx, fy, fz);};
    RVector vector () const {return getVector ();};
    double getT () const { return ft;};
    double t () const { return getT ();};
    double x () const { return fx;};
    double y () const { return fy;};
    double z () const { return fz;};
    double theta () const {return acos (fz/sqrt(fx*fx+fy*fy+fz*fz));}
    double getE () const {return ft;};
    double E () const {return getE ();};
    double beta () const;
    double gamma () const;
    void boost (const RLorentz & kuda, int sign = 1);
    void LorentzTransform (const RLorentz & restFrame);
    void LorentzInverseTransform (const RLorentz & toLVector);
    double getM () const;
    double m () const {return getM ();};
    std::string str () const;
};

RLorentz operator+ (const RLorentz& left, const RLorentz& right);
RLorentz operator- (const RLorentz& left, const RLorentz& right);
double operator* (const RLorentz& left, const RLorentz& right);
RLorentz operator* (const double & left, const RLorentz& right);
RLorentz operator* (const RLorentz& left, const double & right);

