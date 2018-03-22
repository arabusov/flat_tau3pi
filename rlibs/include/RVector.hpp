#pragma once
#include <string>
#include <cmath>
class RVector
{
  private:
    double fx, fy, fz;
  public:
    RVector () {fx=0; fy=0; fz=0;};
    RVector (double x, double y, double z) { fx=x; fy=y; fz=z;};
    double getX() const {return fx;};
    double getY() const {return fy;};
    double getZ() const {return fz;};
    double x() const {return fx;};
    double y() const {return fy;};
    double z() const {return fz;};
    void getXYZ (double & X, double & Y, double & Z) const
      {X=fx;Y=fy;Z=fz;};
    void setX(double x) {fx=x;};
    void setY(double y) {fy=y;};
    void setZ(double z) {fz=z;};
    RVector proj (const RVector & direction) const ;
    double length () const;
    std::string str () const;
    double getCosTh () const {return fz/sqrt(fx*fx+fy*fy+fz*fz);}
};


RVector operator+ (const RVector& left, const RVector& right);
RVector operator- (const RVector& left, const RVector& right);
double operator* (const RVector& left, const RVector& right);
RVector operator* (const double & left, const RVector& right);
RVector operator* (const RVector& left, const double & right);
