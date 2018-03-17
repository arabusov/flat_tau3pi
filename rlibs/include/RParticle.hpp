#pragma once
#include <string>
#include <vector>
#include "RVector.hpp"
#include "RLorentz.hpp"

class RParticleType
{
  private:
    std::string name;
    int PDGid;
    double mass;
    int charge;
  public:
    double Mass () const {return mass;};
    RParticleType (std::string fname, int fPDGid, double fmass, int fcharge);
    RParticleType chargeConjugation () const {return RParticleType (name, -PDGid, mass,
      -charge);};
};

class RParticleTable
{
  public:
    static RParticleTable& Instance()
    {
        static RParticleTable s;
        return s;
    };
		std::vector <RParticleType> particles;
  private:
    RParticleTable();
    ~RParticleTable();

    RParticleTable(RParticleTable const&)=delete; 
    RParticleTable& operator= (RParticleTable const&)=delete;
};

class RParticle
{
  private:
    RLorentz P;
    RVector X; //lol, Heisenberg would be very surprized
    std::vector <RParticleType>::iterator type_iterator;
  public:
    RParticle (std::string name, const RVector& fP, const RVector &fX);
    void dump ()const;
    double mass () const {return type_iterator->Mass ();};
    RLorentz getP () const {return P;};
    void boost (const RLorentz & kuda) {P.boost (kuda);};
};    
