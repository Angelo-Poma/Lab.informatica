#include "TRandom.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <TStyle.h>
#include <cmath>
#include <iostream>
#include <iomanip>

void analyse(){
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);
    TFile *file = new TFile("histograms.root");
    //file->ls();
    TH1F * h1 = (TH1F*)file->Get("h1");
    TH1F * h2 = (TH1F*)file->Get("h2");
    TH1F * h3 = (TH1F*)file->Get("h3");
    TH1F * h4 = (TH1F*)file->Get("h4");
    TH1F * h5 = (TH1F*)file->Get("h5");
    TH1F * h6 = (TH1F*)file->Get("h6");
    TH1F * h7 = (TH1F*)file->Get("h7");
    TH1F * h8 = (TH1F*)file->Get("h8");
    TH1F * h9 = (TH1F*)file->Get("h9");
    TH1F * h10 = (TH1F*)file->Get("h10");
    TH1F * h11 = (TH1F*)file->Get("h11");

    TF1 *fgaus = new TF1("fgaus", "gaus", 0.5, 1.3);
    TF1 *f2 = new TF1("f2","[0]", 0, 2*M_PI);
    TF1 *f3 = new TF1("f3","[0]", 0, M_PI);
    TF1 *f4 = new TF1("f4", "expo", 0, 4);
    f4->SetParameter(0,1);
    f4->SetParameter(1,1);
    h2->Fit("f2", "Q", 0, 2*M_PI);
    h3->Fit("f3", "Q", 0, M_PI);
    h4->Fit("f4", "Q", 0, 4);

    TCanvas *c1 = new TCanvas("c1","Various distributions",200,10,600,400);
    c1->Divide(3,3);
    c1->cd(1);
    h1->SetFillColor(kBlue);
    h1->Draw("hist");  
    c1->cd(2);
    h2->SetFillColor(kBlue);
    h2->GetYaxis()->SetRangeUser(0,130000);
    h2->Draw("hist c");  
    f2->Draw("same");
    c1->cd(3);
    h3->SetFillColor(kBlue);
    h3->GetYaxis()->SetRangeUser(0,130000);
    h3->Draw("hist c"); 
    f3->Draw("SAME"); 
    c1->cd(4);
    h4->SetFillColor(kBlue);
    h4->Draw("hist c");  
    f4->Draw("SAME");
    c1->cd(5);
    h5->SetFillColor(kBlue);
    h5->Draw("hist c");  
    c1->cd(6);
    h6->SetFillColor(kBlue);
    h6->Draw("hist c");      

    TCanvas *c2 = new TCanvas("c2","Invariant mass histograms",200,10,600,400);
    c2->Divide(2,2);
    c2->cd(1);
    h7->SetFillColor(kBlue);
    h7->Draw("hist");
    c2->cd(2);
    h8->SetFillColor(kBlue);
    h8->Draw("hist");
    c2->cd(3);
    h9->SetFillColor(kBlue);
    h9->Draw("hist c");
    c2->cd(4);
    h10->SetFillColor(kBlue);
    h10->Draw("hist c");

    std::cout<<"Particle count:"<<'\n'<<std::setprecision(3)<<std::scientific
    <<"pion+    "<<h1->GetBinContent(1)<<" +/- " <<h1->GetBinError(1)<<"     pion-   "<<h1->GetBinContent(2)<<" +/- " <<h1->GetBinError(2)<<'\n'
    <<"kaon+    "<<h1->GetBinContent(3)<<" +/- " <<h1->GetBinError(3)<<"     kaon-   "<<h1->GetBinContent(4)<<" +/- " <<h1->GetBinError(4)<<'\n'
    <<"proton+  "<<h1->GetBinContent(5)<<" +/- " <<h1->GetBinError(5)<<"     proton- "<<h1->GetBinContent(6)<<" +/- " <<h1->GetBinError(6)<<'\n'
    <<"k*       "<<h1->GetBinContent(7)<< "+/- " <<h1->GetBinError(7)<<'\n'<<'\n';
 
    TH1F *h12 = new TH1F("h12","h12",200,0,3.5);
    h12->Add(h7,h8,1,-1);
    TH1F *h13 = new TH1F("h13","h13",150,0,3.5);
    h13->Add(h9,h10,1,-1); 

    TCanvas *c3 = new TCanvas("c3","Subtraction histograms and control",200,10,600,400);
    c3->Divide(3,1);
    c3->cd(1);
    h11->SetFillColor(kBlue);
    h11->GetYaxis()->SetRangeUser(0, 20000);
    h11->Draw("hist");
    h11->Fit("fgaus","Q");
    fgaus->Draw("same");
    c3->cd(2);
    h12->SetFillColor(kBlue);
    h12->GetYaxis()->SetRangeUser(0, 20000);
    h12->Draw("hist");
    h12->Fit("fgaus","Q");
    fgaus->Draw("same");
    c3->cd(3);
    h13->SetFillColor(kBlue);
    h13->GetYaxis()->SetRangeUser(0, 20000);
    h13->Draw("hist"); 
    h13->Fit("fgaus","Q");
    fgaus->Draw("same");

    std::cout<<std::setw(13)<<"Fit stats"<<std::setw(10)<<"Params"<<std::setw(50)<<"X2/NDF"<<std::setw(10)<<"prob\n"
    <<"azimuthal pol0: "<<f2->GetParameter(0)<<" +/- "<<f2->GetParError(0)<<std::setw(14)<<f2->GetChisquare()<<"/"<<f2->GetNDF()<<std::setw(12)<<f2->GetProb()<<'\n'
    <<"polar pol0:     "<<f3->GetParameter(0)<<" +/- "<<f3->GetParError(0)<<std::setw(14)<<f3->GetChisquare()<<"/"<<f3->GetNDF()<<std::setw(12)<<f3->GetProb()<<'\n'  
    <<"impulse expo:  "<<f4->GetParameter(1)<<" +/- "<<f4->GetParError(0)<<std::setw(14)<<f4->GetChisquare()<<"/"<<f4->GetNDF()<<std::setw(12)<<f4->GetProb()<<'\n';  
}

