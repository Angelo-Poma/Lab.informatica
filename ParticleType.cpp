#include "ParticleType.h"

ParticleType::ParticleType() : fName("electron"), fMass(1.), fCharge(1) {}
ParticleType::ParticleType(char* const name, double const mass,
                           int const charge)
    : fName(name), fMass(mass), fCharge(charge) {}
char* ParticleType::GetName() const { return fName; }
double ParticleType::GetMass() const { return fMass; }
int ParticleType::GetCharge() const { return fCharge; }
void ParticleType::Print() const {
  std::cout << " " << fName << " " << fMass << " " << fCharge;
}
double ParticleType::GetWidth() const {
  return 0;
};


