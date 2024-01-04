#include "Particle.h"
#include "TRandom.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"

int Main () {
    gRandom->SetSeed();
    double phi;
    double theta;
    double p;
    int n; 
    
    const int Nevents (1e5); //#aggiustare
    const int NeventsParticles (120);
    Particle EventsParticles [NeventsParticles];

    Particle::AddParticleType ("pione+", 0.13957, 1);
    Particle::AddParticleType ("pione-", 0.13957, -1);
    Particle::AddParticleType ("Kaone+", 0.49367, 1);
    Particle::AddParticleType ("Kaone-", 0.49367, -1);
    Particle::AddParticleType ("protone+", 0.93827, 1);
    Particle::AddParticleType ("protone-", 0.93827, -1);
    Particle::AddParticleType ("K*", 0.89166, 0, 0.050);

    //#tutti i valori assegnati agli istogrammi sottostanti sono di origine puramente stocastica. a parte, forse, il primo

    TH1F *h1 = new TH1F("h1", "Particles types", 10, 0, 10);
    TH1F *h2 = new TH1F("h2", "azimuthal angles", 100, 0, 2 * M_PI);
    TH1F *h3 = new TH1F("h3", "polar angles", 100, 0, M_PI);
    TH1F* h4 = new TH1F("h4", "Impulse", 100, 0, 4);
    TH1F* h5 = new TH1F("h5", "Transverse impulse", 1000, 0, 3);
    TH1F* h6 = new TH1F("h6", "energy", 100, 0., 3.5);
    TH1F* h7 = new TH1F("h7", "Invariant mass: discordant charge particles", 200, 0., 5);
    TH1F* h8 = new TH1F("h8", "Invariant mass: concordant charge particles", 200, 0., 5);
    TH1F* h9 = new TH1F("h9", "Invariant mass: pion+/kaon- and pion-/kaon+", 150, 0., 5);
    TH1F* h10 = new TH1F("h10", "Invariant mass: pion+/kaon+ and pion-/kaon-", 150, 0., 5);
    TH1F* h11 = new TH1F("h11", "Invariant mass between particles generated from decayment", 60, 0., 1.5);

    h7->Sumw2();
    h8->Sumw2();
    h9->Sumw2();
    h10->Sumw2();
    h11->Sumw2();

    for(int j = 0; j < Nevents; j++){
        n = 0;
        for(int i = 0; i < NeventsParticles - 20; i++){
            double range = gRandom->Uniform();    
            phi = gRandom->Uniform() * 2*M_PI;
            theta = gRandom->Uniform() * M_PI;
            p = gRandom->Exp(1); 
            EventsParticles[i].SetP(p*cos(theta)*cos(phi), p*cos(theta)*sin(phi), p*sin(theta));
            if(range <= 0.4){
                EventsParticles[i].Setter("pione+");
            }
            else if(range <= 0.8){
                EventsParticles[i].Setter("pione-");
            }
            else if(range <= 0.85){
                EventsParticles[i].Setter("Kaone+");
            }
            else if(range <= 0.9){
                EventsParticles[i].Setter("Kaone-");
            } 
            else if(range <= 0.945){
                EventsParticles[i].Setter("protone+");
            }
            else if(range <= 0.99){
                EventsParticles[i].Setter("protone-"); 
            }
            else{
                EventsParticles[i].Setter("K*");
            }

            //#std::cout << "sono qui " << j << std::endl; ##
         if (EventsParticles[i].GetIndex() == 6) {   //#mi sto riferendo all'index di K*
            double aRNDM;
            aRNDM = gRandom->Uniform();
            if (aRNDM <= 0.5) {
                EventsParticles[100 + n].Setter(0);
                EventsParticles[100 + n + 1].Setter(3);
                EventsParticles[i].Decay2body(EventsParticles[100 + n], EventsParticles[100 + n + 1]);
            } else {
                EventsParticles[100 + n].Setter(1);
                EventsParticles[100 + n + 1].Setter(2);
                EventsParticles[i].Decay2body(EventsParticles[100 + n], EventsParticles[100 + n + 1]);
            } 
            h11->Fill(EventsParticles[100 + n].InvMass(EventsParticles[100 + n + 1]));
            n = n + 2;
        }

            h1->Fill(EventsParticles[i].GetIndex());
            h2->Fill(phi);
            h3->Fill(theta);
            h4->Fill(p);
            h5->Fill(sqrt(pow(p*cos(theta)*cos(phi), 2) + pow(p*cos(theta)*sin(phi), 2)));
            h6->Fill(EventsParticles[i].GetEnergy());

        }

      for (int i = 0; i < 100 + n; i++){ //#prima tutti erano +n/2
        if(EventsParticles[i].GetIndex() != 6){ //#aggiunto questo pezzo così non vengono calcolate le masse invarianti di K*, proibito dal FAQ 2
            for(int k = i + 1 ; k < 100 + n; k++){
                if(EventsParticles[k].GetIndex() != 6){ //#aggiunto questo pezzo così non vengono calcolate le masse invarianti di K*, proibito dal FAQ 2
                    
                if(EventsParticles[i].GetCharge()*EventsParticles[k].GetCharge() < 0){
                    h7->Fill(EventsParticles[i].InvMass(EventsParticles[k]));

                    if((EventsParticles[i].GetIndex() == 0 && EventsParticles[k].GetIndex() == 3) ||
                     (EventsParticles[k].GetIndex() == 0 && EventsParticles[i].GetIndex() == 3) ||
                      (EventsParticles[i].GetIndex() == 1 && EventsParticles[k].GetIndex() == 2) ||
                       (EventsParticles[k].GetIndex() == 1 && EventsParticles[i].GetIndex() == 2)){
                        h9->Fill(EventsParticles[i].InvMass(EventsParticles[k]));
                    }
                }
                else if(EventsParticles[i].GetCharge()*EventsParticles[k].GetCharge() > 0) {
                    h8->Fill(EventsParticles[i].InvMass(EventsParticles[k])); 

                    if((EventsParticles[i].GetIndex() == 0 && EventsParticles[k].GetIndex() == 2) ||
                     (EventsParticles[k].GetIndex() == 0 && EventsParticles[i].GetIndex() == 2) ||
                      (EventsParticles[i].GetIndex() == 1 && EventsParticles[k].GetIndex() == 3) || 
                       (EventsParticles[k].GetIndex() == 1 && EventsParticles[i].GetIndex() == 3)){
                        h10->Fill(EventsParticles[i].InvMass(EventsParticles[k]));
                    }
                } 
              }
            } 
        }
      }     
    }     
    
    TFile *file = new TFile("histograms.root", "RECREATE"); //#ha senso recreate?
    file->WriteObject(h1, "h1");
    file->WriteObject(h2, "h2");
    file->WriteObject(h3, "h3");
    file->WriteObject(h4, "h4");
    file->WriteObject(h5, "h5");
    file->WriteObject(h6, "h6");
    file->WriteObject(h7, "h7");
    file->WriteObject(h8, "h8");
    file->WriteObject(h9, "h9");
    file->WriteObject(h10, "h10");
    file->WriteObject(h11, "h11");
    file->Close();

   return 0;
}