/*
 * Simple generator of tau decay to 3 pi nu without hadron dynamics
 * (so-called flat MC)
 * All calculations in tau rest frame
 */
#include <iostream>
#include <random>

void genEvent (std::random_device & rd)
{
  double r = genFlat (rd, 1,2);
  double theta = acos(sqrt (r-1));
  double phi = genFlat (rd, 0,2*pi);
  double P=1.;
  RVector Ptau (P*sin(theta)*cos(phi),P*sin(theta)*sin(phi),P*cos(theta));
  RVector Xtau (0,0,0);
  RParticleList plist = genDecay (rd, Ptau, Xtau);
}

int main (int argc, char ** argv)
{
  std::random_device rd; //initial seed
  for (unsigned int i = 0; i < 100000; i++)
  {
    genEvent (rd);   
  }
  return 0;
}

