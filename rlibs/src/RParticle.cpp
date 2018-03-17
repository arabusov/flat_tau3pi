#include "RParticle.hpp"
#include <iostream>
#include <algorithm>    // std::find
#include <cmath>

RParticleType::RParticleType (std::string fname, int fPDGid, double fmass, int
fcharge)
{
  name = fname;
  PDGid = fPDGid;
  mass = fmass;
  charge = fcharge;
}

RParticleTable::RParticleTable ()
{
	particles.push_back(RParticleType ("tau", 15, 1.777, -1));
	particles.push_back(RParticleType ("pi",111, 0.139, 1));
	particles.push_back(RParticleType ("nutau", 16, 0.001, 0));
}

RParticleTable::~RParticleTable ()
{
	particles.clear();
}

void RParticle::dump ()const
{
  std::cout << "Blah" << std::endl;
}

RParticle::RParticle (std::string name, const RVector& fP, const RVector &fX)
{
  X=fX;
  std::vector <RParticleType>::iterator it;
  RParticleTable & table = RParticleTable::Instance();
  for (auto & it: table.particles)
  {
    if (it->getName () == name)
      type_iterator=it;
  }
  double E = sqrt (
    type_iterator.Mass ()*type_iterator.Mass ()+fP*fP);
}


