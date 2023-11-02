//CodeTest.cpp

#include "ResonanceType.cpp"
#include "ParticleType.cpp"
#include "Particle.cpp"

int main() {
  // ParticleType e1;  standard values were (electron, 1, -1)
  ParticleType e2("muon", 3, -1);
  ResonanceType p("proton", 10, +1, 100);

  std::cout << /* e1.GetName() <<  " " << e1.GetMass() */ " " << e2.GetCharge()
            << " " << p.GetName() << " " << p.GetMass() << " " << p.GetCharge()
            << " " << p.GetWidth() << '\n';

  e2.Print();
  std::cout << '\n';
  p.Print();
  std::cout << '\n';

  char* type_array[2] = {"electron","proton"};  // # non saprei se un erray del genere quando il testo dice "un array che identifica ParticleType"
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      e2.Print();
      std::cout << '\n';
    } else if (i == 1) {
      p.Print();
      std::cout << '\n';
    }
  }
}