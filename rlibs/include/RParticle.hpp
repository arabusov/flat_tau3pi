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
    double ctau;
    int charge;
  public:
    RParticleType () {};
    double Mass () const {return mass;};
    double getCTau () const {return ctau;};
    std::string getName () const {return name;};
    RParticleType (std::string fname, int fPDGid, double fmass, double fctau, int fcharge);
    RParticleType chargeConjugation () const {return RParticleType (name,
    -PDGid, mass, ctau, 
      -charge);};
    std::string str () const;
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
    RParticleType type;
  public:
    RParticle () {}
    RParticle (std::string name, const RVector& fP, const RVector &fX);
    void dump ()const;
    double mass () const {return type.Mass ();}
    RLorentz getP () const {return P;}
    RVector getX () const {return X;}
    void boost (const RLorentz & kuda) {P.boost (kuda);}
    void LorentzTransform (const RLorentz & lv) {P.LorentzTransform (lv);}
    void setP(const RVector &fP);
    void setX(const RVector &fX);
    double E () const {return P.E();}
    void chargeConjugate () {type=type.chargeConjugation ();}
    double getCTau () const {return type.getCTau ();}
};    
