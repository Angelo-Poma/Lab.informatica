#include "ParticleType.h"

ParticleType::ParticleType() : fName_("electron"), fMass_(1.), fCharge_(1) {}
ParticleType::ParticleType(char* const name, double const mass,
                           int const charge)
    : fName_(name), fMass_(mass), fCharge_(charge) {}
char* ParticleType::GetName() const { return fName_; }
double ParticleType::GetMass() const { return fMass_; }
int ParticleType::GetCharge() const { return fCharge_; }
void ParticleType::Print() const {
  std::cout << " " << fName_ << " " << fMass_ << " " << fCharge_;
};

