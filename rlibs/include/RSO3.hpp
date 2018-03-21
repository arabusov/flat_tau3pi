#pragma once
#include <string>
#include "RVector.hpp"

class RSO3
{
  private:
    double a[3][3];
  public:
    RSO3 ();
    RSO3 (double phi, unsigned int axis);
    void rotate (double phi, unsigned int axis);
    RVector operator* (const RVector & right);
    RSO3 operator= (const RSO3 & right);
    RVector getRow (unsigned int row) const;
    RVector getColumn (unsigned int column) const;
    double getElement (unsigned int row, unsigned int column)const ;
    void setElement (unsigned int row, unsigned int column,double val);
    void EulerTransform (double phi, double theta, double psi);
};

RSO3 operator* (const RSO3 & left, const RSO3 & right);
RVector operator* (const RVector & left, const RSO3 & right);

