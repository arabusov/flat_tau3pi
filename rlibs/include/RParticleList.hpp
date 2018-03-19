#pragma once
#include <vector>
#include "RParticle.hpp"

class RParticleList
{
  private:
    std::vector <RParticle> particles_vector;
  public:
    RParticleList () {};
    ~RParticleList ()
      {particles_vector.clear();};
    void add (const RParticle & particle)
      {particles_vector.push_back (particle);};
    void dump () const 
      {for (const auto & it: particles_vector) 
        it.dump();
      }; 
    std::vector <RParticle> getList () const {return particles_vector;};
};
