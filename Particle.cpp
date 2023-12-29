#include "Particle.h"
#include <cstdlib>

ParticleType* Particle::fParticleType[Particle::fMaxNumParticleType]; 
int Particle::fNParticleType = 0;

int Particle::FindParticle(char* name) {  // un nome più descrittivo sarebbe FindParticleIndex
  for (int i = 0; i < fNParticleType; i++) {
    if (fParticleType[i]->GetName() == name) {
      return i;
    }
    }
    return -1;
}

Particle::Particle(char* name, double Px = 0, double Py = 0, double Pz = 0)
    : fPx(Px), fPy(Py), fPz(Pz) {
  if (FindParticle(name) == -1) {
    throw std::runtime_error{"No corresponding particle type found \n"};
  }
  else{fIndex = FindParticle(name);}
}

Particle::Particle()
    {
  fIndex = -1;
  fPx = 0;
  fPy = 0;
  fPz = 0;
}

int Particle::GetIndex() { return fIndex;}

void Particle::AddParticleType(char* name, double mass, int charge, double width){  //potrebbe creare problemi l'inizializzazione di width a 0
    if(FindParticle(name) != -1){
        std::cout<<"Particle already inserted in index number "<<FindParticle(name) << '\n';
    }
    else if(FindParticle(name) == -1 && fNParticleType == fMaxNumParticleType){
        std::cout<<"Maximum number of saved particles already reached \n"; //??si deve mettere un error
    }
    else{
        if(width == 0) {
        fParticleType[fNParticleType] = new ParticleType(name, mass, charge);
        fNParticleType ++;}
        else {
             fParticleType[fNParticleType] = new ResonanceType(name, mass, charge, width);
             fNParticleType ++;
        }
    }
}
void Particle::PrintArray(){
  for(int i = 0; i < fNParticleType; i++){
    std::cout<<fParticleType[i]->GetName()<<" "; //??dubbio
  } std::cout << std::endl;
}
void Particle::PrintInfo(){
  std::cout << "Index: " << fIndex << ", name:  " << fParticleType[fIndex]->GetName() << ", momentum:  " << fPx << ", " << fPy << ", " << fPz << '\n';
}

void Particle::Setter(int index){
    if(fIndex < fNParticleType){
    fIndex = index;
    }
    else{
        throw std::runtime_error{"fIndex larger than number of saved particle types"}; 
    }
}
void  Particle::Setter(char* name){fIndex = FindParticle(name);}

void Particle::SetP(double Px, double Py, double Pz){
  fPx = Px;
  fPy = Py;
  fPz = Pz;

}

const double Particle::GetPx() const {
  return fPx;
}
const double Particle::GetPy() const {
  return fPy;
}
const double Particle::GetPz() const{
  return fPz;
}
const double Particle::GetMass() const{ 
  return fParticleType[fIndex]->GetMass(); //non siamo certi, magari serve un -1
}
const double Particle::GetCharge() const{
  return fParticleType[fIndex]->GetCharge();
}
const double Particle::GetEnergy() const{
  return sqrt(GetMass()*GetMass() + (fPx*fPx + fPy*fPy + fPz*fPz)); 
}
const double Particle::InvMass(Particle& p) const{
  return sqrt(pow(GetEnergy() + p.GetEnergy() , 2 ) - (pow((fPx + p.fPx) , 2) + pow((fPy + p.fPy) , 2) + pow((fPz + p.fPz) , 2) ) );
}

//////////////////////////////////////////////////////////////////////////////////////
/////// #roba copiata dalla prof# ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIndex > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;

    massMot += fParticleType[fIndex]->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

  double bx = fPx/energy;
  double by = fPy/energy;
  double bz = fPz/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx + by*fPy + bz*fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx += gamma2*bp*bx + gamma*bx*energy;
  fPy += gamma2*bp*by + gamma*by*energy;
  fPz += gamma2*bp*bz + gamma*bz*energy;}







