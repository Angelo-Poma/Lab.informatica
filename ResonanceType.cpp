#include "ResonanceType.h"

ResonanceType::ResonanceType(char* const name, double const mass,
                             int const charge, double width)
    : ParticleType(name, mass, charge), fWidth_(width) {}
double ResonanceType::GetWidth() const { return fWidth_; }
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << " " << fWidth_;
};