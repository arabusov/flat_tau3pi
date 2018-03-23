#include <cmath>
#include "RVector.hpp"
#include <string>
#include <sstream>
#include <iostream>
RVector operator+ (const RVector& left, const RVector& right)
{
  RVector res (
    left.x()+right.x(),   
    left.y()+right.y(),   
    left.z()+right.z());
  return res;
}
  
RVector operator- (const RVector& left, const RVector& right)
{
  return left+(-1.)*right;
}

double operator* (const RVector& left, const RVector& right)
{
  double res =
    left.x()*right.x()+
    left.y()*right.y()+   
    left.z()*right.z();
  return res;
}

RVector operator* (const RVector& left, const double& right)
{
  RVector res (
    left.x()*right,   
    left.y()*right,   
    left.z()*right);
  return res;
}

RVector operator* (const double & left, const RVector & right)
{
  return right*left;
}

double RVector::length () const
{
  return sqrt ((*this)*(*this));
}

RVector RVector::proj (const RVector & direction) const
{
  RVector result (0,0,0);
  double dd = direction*direction;
  if (dd > 0)
  {
    result = ((direction*(*this))/dd)*direction;
  }
  return result;  
}

std::string RVector::str () const
{
  std::stringstream ss;
  ss << fx << " " << fy << " " <<fz ;
  return ss.str();
}
