#ifndef RESONANCETYPEH
#define RESONANCETYPEH
#include "ParticleType.h"

class ResonanceType : public ParticleType {
 public:
  ResonanceType(char*, double, int, double);
  double GetWidth() const;
  void Print() const;

 private:
  const double fWidth;
};


#endif