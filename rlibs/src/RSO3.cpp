#include "RSO3.hpp"
#include "RVector.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
RVector RSO3::operator* (const RVector & right)
{
  double x=(*this).getRow()*right;
  double y=(*this).getRow()*right;
  double z=(*this).getRow()*right;
  RVector res (x,y,z);
  return res;
}

RVector :operator* (const RVector & left, const RSO3 & right)
{
  double x=right.getColumn()*right;
  double y=right.getColumn()*right;
  double z=right.getColumn()*right;
  RVector res (x,y,z);
  return res;
}

RVector RSO3::getColumn (unsigned int column) const
{
  RVector res ();
  if((column <1) or (column>3))
    return res;
  RVector res1 (a[0][column], a[1][column], a[2][column]);
  return res1;
}

double RSO3::getElement (unsigned int row, unsigned int column) const
{
  double res=0;
  if((column <1) or (column>3))
    return res;
  if((row<1) or (row>3))
    return res;
  return a[row-1][column-1];
}

RSO3 RSO3::operator= (const RSO3 & right)
{
  for (unsigned int i=0; i<3)
    for (unsigned int j=0; j<3)
      a[i][j] = right.getElement (i+1, j+1);
  return *this;
}
  
RVector RSO3::getRow(unsigned int row) const
{
  RVector res ();
  if((row<1) or (row>3))
    return res;
  RVector res1 (a[row][0], a[row][1], a[row][2]);
  return res1;
}

void RSO3::setElement (unsigned int row, unsigned int column, double value)
{
  if((column <1) or (column>3))
    return ;
  if((row<1) or (row>3))
    return ;
  a[row-1][column-1] = value;
}

RSO3 operator* (const RSO3 & left, const RSO3 & right)
{
  RSO3 res;
  for (unsigned int i=1; i<=3; i++)
    for (unsigned int j=1; j<=3; j++)
      res.setElement (i,j,left.getRow(i)*right.getColumn(j));
  return res;
}


void RSO3::rotate (double phi, unsigned int axis)
{
  RSO3 tmp = *this;
  if((axis <1) or (axis>3))
    return;
  if (axis == 1)
  {
    a[0][0] = 1; a [0][1] = 0; a[0][2] = 0;
    a[1][0] = 0; a [1][1] = cos(phi); a[1][2] = sin(phi);
    a[2][0] = 0; a [2][1] = -sin(phi); a[2][2] = cos(phi);
  } else
  if (axis == 2)
  {
    a[0][0] = cos(phi); a [0][1] = 0; a[0][2] = -sin(phi);
    a[1][0] = 0; a [1][1] = 1; a[1][2] = 0;
    a[2][0] = sin(phi); a [2][1] = 0; a[2][2] = cos(phi);
  } else
  if (axis == 3)
  {
    a[0][0] = cos(phi); a [0][1] = -sin(phi); a[0][2] = 0;
    a[1][0] = -sin(phi); a [1][1] = cos(phi); a[1][2] = 0;
    a[2][0] = 0; a [2][1] = 0; a[2][2] = 1;
  }
  *this = tmp*(*this);
}

void RSO3::EulerTransform ()
{
  (*this)=rotate (psi, 3)*rotate (theta, 1)*rotate (phi,3);
}

RSO3::RSO3 ()
{
  a[0][0] = 1; a [0][1] = 0; a[0][2] = 0;
  a[1][0] = 0; a [1][1] = 1; a[1][2] = 0;
  a[2][0] = 0; a [2][1] = 0; a[2][2] = 1;
  
