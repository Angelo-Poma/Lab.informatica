#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H
#include "ParticleType.h"

class ResonanceType : public ParticleType {
 public:
  ResonanceType(char*, double, int, double);
  double GetWidth() const;
  void Print() const;

 private:
  const double fWidth_;
};


#endif