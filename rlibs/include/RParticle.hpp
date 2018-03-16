#pragma once
#include "RVector.hpp"
#include "RLorentz.hpp"

struct ParticleType
{
  std::string name;
  int PDGid;
  double mass;
  int charge;
  ParticleType (std::string fname, int fPDGid, double fmass, int fcharge)
  ParticleType chargeConjugation () {return ParticleType (name, -PDGid, mass,
    -charge);
};

typedef struct ParticleType RParticleType;

RParticleType ParticleTable [3] = {
  {"tau", 15, 1.777, -1},
  {"pi",111, 0.139, 1},
  {"nutau", 16, 0.001, 0}};


class RParticle
{
  private:
    RLorentz P;
    RVector xx; //lol, Heisenberg would be very surprized
    RParticleType type;
  public:
    
