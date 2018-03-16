#pragma once
#include <vector>
#include "RParticle.hpp"

class RParticleList
{
  private:
    std::vector <RParticle> particles_vector;
  public:
    ~RParticleList () {particle_vector.clear();};
    void add (RParticle & particle) {particles_vector.push_back (particle);};
    void dump () const {for (const auto & it: particles_vector) it.dump();}; 
};
