#ifndef PARTICLE_H
#define PARTICLE_H
#include "ResonanceType.h"


class Particle {
 public:
  Particle(); //??è necessario per il vettore in main di Particle?
  Particle(char*, double, double, double);
  static void AddParticleType(char* name, double mass, int charge, double width = 0);  
  int GetIndex();

  void static PrintArray();
  void PrintInfo();
  
  void Setter(int); 
  void Setter(char*); //??rimpiazza il un dato dell'array con il nome dell'argomento con un'altra particella?
  void SetP(double, double, double);
 

  const double GetPx() const;
  const double GetPy() const;
  const double GetPz() const;
  const double GetMass() const;
  const double GetCharge() const;
  const double GetEnergy() const;
  const double InvMass(Particle& p) const;

  int Decay2body(Particle &dau1,Particle &dau2) const;
  
   private:
  void Boost(double bx, double by, double bz);

 private:
  static const int fMaxNumParticleType = 
      10; 
  static ParticleType* fParticleType[fMaxNumParticleType]; //#non è un membro come previsto dalle slide, quindi può essere sbagliato
  static int fNParticleType;
  int fIndex;
  double fPx;
  double fPy;
  double fPz;

  static int FindParticle(char*);
};

#endif