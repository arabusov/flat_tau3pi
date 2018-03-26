#include "RParticle.hpp"
#include <iostream>
#include <algorithm>    // std::find
#include <cmath>
#include <string>
#include <sstream>

RParticleType::RParticleType (std::string fname, int fPDGid, double fmass,
double fctau, int fcharge)
{
  name = fname;
  PDGid = fPDGid;
  mass = fmass;
  ctau = fctau;
  charge = fcharge;
}

std::string RParticleType::str () const
{
  std::stringstream ss;
  ss << "Type: " << name << ", Charge: " << charge;
  return ss.str();
}
RParticleTable::RParticleTable ()
{
	particles.push_back(RParticleType ("tau", 15, 1.77686, 0.08703, -1));
	particles.push_back(RParticleType ("pi",111, 0.13957018,7804.5, 1));
	particles.push_back(RParticleType ("nutau", 16, 0.001,1e8,0));
}

RParticleTable::~RParticleTable ()
{
	particles.clear();
}

void RParticle::dump ()const
{
  std::cout << type.str() << " " << ", P: " << P.str() << ", X: " << X.str();
  std::cout << std::endl;
}

RParticle::RParticle (std::string name, const RVector& fP, const RVector &fX)
{
  X=fX;
  RParticleTable & table = RParticleTable::Instance();
  for (auto & it: table.particles)
  {
    if (it.getName () == name)
      type=it;
  }
  setP (fP);
}

void RParticle::setP (const RVector & fP)
{
  double E = sqrt (
    type.Mass ()*type.Mass ()+fP*fP);
  P = RLorentz (E, fP.x(), fP.y(), fP.z());
}

void RParticle::setX (const RVector & fX)
{
  X = fX;
}
