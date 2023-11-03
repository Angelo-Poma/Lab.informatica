#include "Particle.cpp"
#include "TRandom.h"

int main () {
    gRandom->SetSeed();
    double phi;
    double theta;
    double p;
    
    const int Nevents (10^5);
    const int NeventParticles (120);
    Particle EventParticles [120];

    Particle::AddParticleType ("pione+", 0.13957, 1);
    Particle::AddParticleType ("pione-", 0.13957, -1);
    Particle::AddParticleType ("Kaone+", 0.49367, 1);
    Particle::AddParticleType ("Kaone-", 0.49367, -1);
    Particle::AddParticleType ("protone+", 0.93827, 1);
    Particle::AddParticleType ("protone-", 0.93827, -1);
    Particle::AddParticleType ("K*", 0.89166, 0, 0.050);

    for(int i = 0; i < Nevents; i++){
        for(int i = 0; i < NeventParticles; i++){
            double range = gRandom->Uniform();    
            phi = gRandom->Uniform() * 2*M_PI;
            theta = gRandom->Uniform() * M_PI;
            p = gRandom->Exp(); //da finire ##
            EventParticles[i].SetP(p*cos(theta)*cos(phi), p*cos(theta)*sin(phi), p*sin(theta))
            if(range <= 0.4){
                EventParticles[i].Setter("pione+");
            }
            else if(0.4 < range <= 0.8){
                EvenParticles[i].Setter("pione-");
            }
            else if(0.8 < range <= 0.85){
                EvenParticles[i].Setter("kaone+");
            }
            else if(0.85 < range <= 0.9){
                EvenParticles[i].Setter("kaone-");
            } 
                  
        }
    }
}