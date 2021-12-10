#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TCut.h"
#include "TRandom3.h"
#include "TError.h"
#include "TLegend.h"
#include "TString.h"
#include <iostream>

static void show_usage()
{
  std::cerr << "Usage: ./sim <options>\n"
            << "Options:\n"
            << "\t-i,--input\t\tInput ROOT file\n"
            << "\t-o,--output\t\tOutput image\n"
            << std::endl;
}

int main(int argc, char** argv) {

  char* filename;
  char* output;

  // Parse the command line                                                                                                                                                
  std::string input;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if ((arg == "-h") || (arg == "--help")) {
      show_usage();
      return 0;
    }
    if ((arg == "-i") || (arg == "--input"))
      filename = argv[i+1];
    if ((arg == "-o") || (arg == "--output"))
      output = argv[i+1];
  }


  std::cout << "Input file: " << filename << std::endl;
  TFile *f1 = new TFile(filename);
  TTree *t1 = (TTree*)f1->Get("Scoring");

  Int_t Track, PDG;
  Double_t Edep, Length;

  t1->SetBranchAddress("fTrack",&Track);
  t1->SetBranchAddress("fPDG",&PDG);
  t1->SetBranchAddress("fEdep",&Edep);
  t1->SetBranchAddress("fLength",&Length);
 
  TH2F *e = new TH2F("e","Edep vs Length",50, 0., 150., 100, 0., 2.);
  TH2F *gamma = new TH2F("gamma","Edep vs Length",50, 0., 50000., 100, 0., .003);
  TH2F *dedl = new TH2F("dedl","Edep/l vs Edep",50, 0., 2., 100, 0., 10.);
  TH1F *E_e = new TH1F("E_e","Deposited energy - e",200, 0., 1.5);
  TH1F *E_gamma = new TH1F("E_gamma","Deposited energy - gamma",50, 0., .003);

  Double_t StoppingPower = 0;
  Int_t count = 0;

  Long64_t nentries = t1->GetEntries();
  std::cout << "Entries: " << nentries << std::endl;
  for (Long64_t i=0;i<nentries;i++) {
    t1->GetEntry(i);

    if (PDG==11&&Length>0) e->Fill(Length,Edep);
    if (PDG==11&&Length>0) E_e->Fill(Edep);
    if (PDG==11&&Edep>0&&Length>0) {
      dedl->Fill(Length,Edep/Length) ;
      count++;
      StoppingPower = StoppingPower + Edep/Length;
    }
    
    if (PDG==22&&Length>0) gamma->Fill(Length,Edep);
    if (PDG==22&&Length>0) E_gamma->Fill(Edep);
  }
  

  // Output
  std::cout << "Stopping power: " << StoppingPower/count << std::endl;


  // Plot

  TCanvas *c1 = new TCanvas("c1","Radon",1600,900);
  c1->Divide(3,2);

  c1->cd(1);
  e->Draw("colz");

  c1->cd(2);
  gamma->Draw("colz");

  c1->cd(3);
  dedl->Draw("colz");

  c1->cd(4);
  E_e->Draw("colz");

  c1->cd(5);
  E_gamma->Draw("colz");


  c1->SaveAs(output);
  //  system("display "+(std::string)output+"&");


  
  return 0;

}
