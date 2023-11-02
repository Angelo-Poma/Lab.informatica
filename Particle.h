#ifndef PARTICLE_H
#define PARTICLE_H
#include "ResonanceType.h"


class Particle {
 public:
  Particle(char*, double, double, double);
  static void AddParticleType(char*, double, int, double);  //lo static fa in modo che può essere chiamata senza istanze associate

  int GetIndex();
  void Setter(int); 
  void Setter(char*); //??rimpiazza il un dato dell'array con il nome dell'argomento con un'altra particella?



  


 private:
  static const int fMaxNumParticleType_ = 
      10; 
  static ParticleType* fParticleType_[fMaxNumParticleType_]; //#non è un membro come previsto dalle slide, quindi può essere sbagliato
  static int fNParticleType_;
   int fIndex_;
  double fPx_;
  double fPy_;
  double fPz_;

  static int FindParticle(char*);
};

#endif