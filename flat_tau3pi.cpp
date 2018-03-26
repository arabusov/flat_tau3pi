/*
 * Simple generator of tau decay to 3 pi nu without hadron dynamics
 * (so-called flat MC)
 * All calculations in tau rest frame
 */
#include <iostream>
#include <random>
#include <cmath>
#include "RVector.hpp"
#include "RParticleList.hpp"
#include "RTau3pi.hpp"

RParticleList genEvent (std::mt19937_64 & gen)
{
  std::uniform_real_distribution <> distr;
  double r = distr (gen); 
  double theta = acos(r);
  double phi = 2*3.1415926*distr (gen);
  double P=1.;
  RVector Ptau (P*sin(theta)*cos(phi),P*sin(theta)*sin(phi),P*cos(theta));
  RVector Xtau (0,0,0);
  RTau3pi tau_gen (1.1);//fix a1 mass to 1.1
  return tau_gen.genDecay (Ptau, Xtau);
}
double Cos (const RLorentz & p1, const RLorentz & p2)
{
  RVector a = p1.vector();
  RVector b = p2.vector();
  return a*b/a.length() /b.length();
}

int main (int argc, char ** argv)
{
  std::random_device rd; //initial seed
  std::mt19937_64 gen (rd());
  for (unsigned int i = 0; i < 100000; i++)
  {
    RParticleList plist = genEvent (gen);   
#if 0
RParticle tau = plist.getList ()[0];
    RParticle nu = plist.getList ()[1];
    RParticle pi1 = plist.getList ()[2];
    RParticle pi2 = plist.getList ()[3];
    RParticle pi3 = plist.getList ()[4];
    std::cout <<tau.getX ().length() << " ";
    RLorentz ptau = tau.getP();
    RLorentz pnu = nu.getP();
    RLorentz p1= pi1.getP();
    RLorentz p2= pi2.getP();
    RLorentz p3= pi3.getP();
    RLorentz p3pi = p1+p2+p3;
    std::cout << (ptau-pnu-p3pi).E()<< " ";
    std::cout << ptau*ptau << " " << pnu*pnu << " " << p1*p1 << " " << p2*p2 <<
    " " << p3*p3 << " ";
    std::cout << (p1+p2)*(p1+p2) << " " << (p1+p3)*(p1+p3) << " " <<
    (p2+p3)*(p2+p3) << " ";
    std::cout << p3pi*p3pi << " ";
    std::cout << Cos (pnu, ptau) << " " << Cos (pnu, p3pi) << " " << Cos (p3pi,
    ptau) << " " << Cos (p1,p2) << " " << Cos (p1,p3) << " " << Cos (p2,p3);
#endif
    std::cout << std::endl;
  }
  return 0;
}

