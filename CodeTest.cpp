//CodeTest.cpp

#include "ResonanceType.cpp"
#include "ParticleType.cpp"
#include "Particle.cpp"

int main() {
  // ParticleType e1;  standard values were (electron, 1, -1)
  /*ParticleType e2("muon", 3, -1);
  ResonanceType p("proton", 10, +1, 100);

  std::cout << /* e1.GetName() <<  " " << e1.GetMass()  " " << e2.GetCharge()
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
  }*/

  Particle::AddParticleType("Proteo", 44, 3, 90 );
  Particle::AddParticleType("Typhon", 23, -5 );
  Particle::AddParticleType("Zagreus", 11, 1, 1 );
  Particle::AddParticleType("Atena", 50, -5, 91 );
  Particle::AddParticleType("Efesto", 50, -5, 92 );
  Particle::AddParticleType("Poseidone", 50, -5, 93 );
  Particle::AddParticleType("Asclepio", 50, -5, 94 );
  Particle::AddParticleType("Atlas", 50, -5, 95 );
  Particle::AddParticleType("Ares", 60, -5, 95 );

  /* Particle::AddParticleType("Kratos", 70, -5, 95 );
  Particle::AddParticleType("Andrea", 50, -5, 90 ); */ //error test
  Particle::AddParticleType("Andrea", 50, -5, 90 );
  
  Particle Proteo ("Proteo", 4.14);
  Particle Bromio ("Zagreus", 1, 2, 3.56);
  /* Particle Eggidio ("Asdrubale", 33, 44.44, 6.2 ); //error test */
   
  Particle::PrintArray ();
 Bromio.PrintInfo();
  std::cout << Proteo.GetEnergy () << std::endl;
  std::cout << Bromio.GetEnergy () << std::endl;
  std::cout << Proteo.InvMass (Bromio) << std::endl;
  
  Bromio.SetP (33.3, 44.4, 55.77);
  std::cout << Bromio.GetPz () << std::endl;
}