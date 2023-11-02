#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H
#include <iostream>

class ParticleType {
 public:
  ParticleType();//??non saprei se sia necessario il costruttore default per fare funzionare la derivata
  ParticleType(char*, double, int);
  char* GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual void Print() const;

 private:
   char* fName_;
  const double fMass_;
  const int fCharge_;
};


#endif