#pragma once
#include "RParticleList.hpp"
#include "RVector.hpp"
#include "RLorentz.hpp"
#include <random>

class RTau3pi
{
  private:
    bool is_m3pi_fixed;
    RParticleList plist;
    double mtau, mnu, m3pi, mpi;
    //init masses
    void init_masses ();
    //steps 
    void genTau (const RVector & Ptau, const RVector & Xtau);
    RLorentz genNeutrino ();
    void gen3pi (const RLorentz & P3pi);
    //Tau lepton parameters
    RLorentz Ptau;
    RVector Xtau;
    //just for simpl expr
    double sqr (double x);
    //phase space
    double px (double e1, double e2, double p3, double m, int i=1);
    bool p1xmorep1 (double e1, double e2, double m3pi, double m);
    //random
    void init_random_generator (int seed);
    void init_random_generator ();
    std::mt19937_64 gen;
    double genFlat (double min=-1, double max=1.);
    double genExp (double lambda = -1);
  public:
    RTau3pi ();
    RTau3pi (double m3pi);
    RParticleList genDecay (const RVector & ptau, const RVector & xtau);
};
