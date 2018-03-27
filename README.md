# Tau decay generator
The generator performs M.C. simulation for tau-lepton decay to 3 pions
and one neutrino without dynamics and polarization. I will add this generator
into TAUOLA.
## TODO List
  * Tau charge
  * PDG table of particles
## How to use
Just read flat_tau3pi.cpp file.
```cpp
#include "RVector.hpp"
#include "RLorentz.hpp"
#include "RParticle.hpp"
#include "RParticleList.hpp"
#include "RTau3pi.hpp"

int main ()
{
  RTau3pi tau_gen (1.1);//fix 3pi mass to 1.1 GeV
  RVector Ptau (0.,0.,2.);
  RVector Xtau (0.,0.,0.); //coordinates in mm
  RParticleList plist = tau_gen.genDecay (Ptau, Xtau);
  plist.dump();
  return 0;
}

```
But more useful is the following method after generating the event:
```cpp
  plist.getList ();
```
which returns std::vector of RParticle objects.
## How to compile
```bash
mkdir build
cd build
cmake ../
make
```
## Dalitz plot
A1 meson mass is fixed to 1.1 GeV.
![Here should be the dalitz plot](./example/dalitz.png)
