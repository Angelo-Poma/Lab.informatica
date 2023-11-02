#include "Particle.h"

ParticleType* Particle::fParticleType_[Particle::fMaxNumParticleType_]; 
int Particle::fNParticleType_ = 0;

int Particle::FindParticle(char* name) {  // un nome più descrittivo sarebbe FindParticleIndex
  for (int i = 0; i < fNParticleType_; i++) {
    if (fParticleType_[i]->GetName() == name) {
      return i;
    }
    }
    return -1;
}

Particle::Particle(char* name, double Px = 0, double Py = 0, double Pz = 0)
    : fPx_(Px), fPy_(Py), fPz_(Pz) {
  if (FindParticle(name) == -1) {
    throw std::runtime_error{"No corresponding particle type found \n"};
  }
  else{fIndex_ = FindParticle(name);}
}

int Particle::GetIndex() { return fIndex_;}

void Particle::AddParticleType(char* name, double mass, int charge, double width = 0){  //potrebbe creare problemi l'inizializzazione di width a 0
    if(FindParticle(name) != -1){
        std::cout<<"Particle already inserted in index number \n"<<FindParticle(name);
    }
    else if(FindParticle(name) == -1 && fNParticleType_ == fMaxNumParticleType_){
        std::cout<<"Maximum number of saved particles already reached \n"; //??si deve mettere un error
    }
    else{
        if(width = 0) {
        fParticleType_[fNParticleType_] = new ParticleType(name, mass, charge);
        fNParticleType_ ++;}
        else {
             fParticleType_[fNParticleType_] = new ResonanceType(name, mass, charge, width);
             fNParticleType_ ++;
        }
    }
}

void Particle::Setter(int index){
    if(fIndex_ <= fNParticleType_){
    fIndex_ = index;
    }
    else{
        throw std::runtime_error{"fIndex larger than number of saved particle types"}; 
    }
}
void  Particle::Setter(char* name){fIndex_ = FindParticle(name);}




















/* se ni' mondo ci fosse un po' di bene
ed ognun si considerasse suo fratello
ci srebbero meno dolori e meno PTHREAD_CANCEL_ENABLEed il mondo ne sarebbe assai più _BITS_TYPES_LOCALE_T_H

- Pietro Pacciani
*/