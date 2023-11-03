#ifndef PARTICLETYPEH
#define PARTICLETYPEH
#include <iostream>
#include <cmath>

class ParticleType {
 public:
  ParticleType();//??non saprei se sia necessario il costruttore default per fare funzionare la derivata
  ParticleType(char*, double, int);
  char* GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual void Print() const;
  virtual double GetWidth() const;

 private:
   char* fName;
  const double fMass;
  const int fCharge;
};


#endif