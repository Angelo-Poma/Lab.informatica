#include "ResonanceType.h"

ResonanceType::ResonanceType(char* const name, double const mass,
                             int const charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}
double ResonanceType::GetWidth() const { return fWidth; }
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << " " << fWidth;
};