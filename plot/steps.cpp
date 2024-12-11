/////////////////////////////////////////////////////////
//
// Produces a Stopping power plot:
//  - QUEST-BOX simulation for a specific material and a physics model, compared with
//  - eStar data for that material given as input
//
// Example:   ./steps -i ../build/electron_aluminium.root -m ../scripts/estar_aluminium.dat -d 2.7 -o electron_aluminium.png
//            eog electron_aluminium.png 
/////////////////////////////////////////////////////////


#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
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
            << "\t-m,--model\t\tModel ascii file\n"
            << "\t-d,--density\t\tDensity [g/cm3]\n"

            << std::endl;
}

int main(int argc, char** argv) {

  ////////////////////////////

  float maxE = 10.;  // [MeV]
  float minE = 1e-2;  // [MeV]
  float maxSP = 20.;  // [MeV cm^2/g]
  int PDGId = 11; //1000020040; // PDG ID

  ////////////////////////////

  char* filename;
  char* output;
  char* model;
  float density; // [g/cm3]

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
    if ((arg == "-m") || (arg == "--model"))
      model = argv[i+1];
    if ((arg == "-d") || (arg == "--density"))
      density = atof(argv[i+1]);
  }


  TFile *f1 = new TFile(filename);
  std::cout << "Input file: " << filename << std::endl;
  std::cout << "Density [g/cm3]: " << density << std::endl;
  //  TTree *t1 = (TTree*)f1->Get("Scoring");  // ntuple 1
  TTree *t1 = (TTree*)f1->Get("Stepping");  // ntuple 2

  Int_t Track, PDG, Process;
  Double_t Edep, Length, E;

  t1->SetBranchAddress("fTrack",&Track);
  t1->SetBranchAddress("fPDG",&PDG);
  t1->SetBranchAddress("fEdep",&Edep);
  t1->SetBranchAddress("fE",&E);
  t1->SetBranchAddress("fLength",&Length);
  t1->SetBranchAddress("fProcess",&Process);

  // To be filled from Geant:
  TH2F *dEdxvsE = new TH2F("dEdxvsE","dEdx vs Kinetic Energy",            1000, minE, maxE, 1000, 0.0001, maxSP);
  TH1F *dEdxvsE_histo = new TH1F("dEdxvsE_histo","dEdx vs Kinetic Energy",1000, minE, maxE);
  TGraphErrors* graph_geant = new TGraphErrors(dEdxvsE->GetNbinsX());

  // Graph from eStar:
  TGraph* graph_estar = new TGraph(model, "%lg %lg");

  Double_t StoppingPower = 0;
  Int_t count = 0;

  Long64_t nentries = t1->GetEntries();
  std::cout << "Entries: " << nentries << std::endl;
  for (Long64_t i=0;i<nentries;i++) {
    t1->GetEntry(i);

    //if (PDG==11&&Edep>0&&Length>0&&Process==3) {
    
    // Select only primary electrons
    if (Track==1&&PDG==PDGId&&Edep>0&&Length>0) {
          
      // filling 2D histo:
      dEdxvsE->Fill(E,10/density*Edep/Length);
      count++;
      StoppingPower = StoppingPower + 10/density*Edep/Length;

    }
  }
  
  // Output
  std::cout << "Selected steps: " << count << std::endl;
  std::cout << "Average stopping power: " << StoppingPower/count << std::endl;

  // Project to 1D histogram
  for ( Int_t bin = 1; bin < dEdxvsE->GetNbinsX(); bin++ ){
    TH1D *prof = dEdxvsE->ProjectionY("prof",bin,bin+1,"");
    
    // Average Stopping Power possibilities:
    Double_t SP = prof->GetMean();
    //Double_t SP = prof->GetMaximumBin()*maxSP/1000.;

    dEdxvsE_histo->SetBinContent(bin, SP);
    dEdxvsE_histo->SetBinError(  bin, prof->GetRMS()/sqrt(prof->GetEntries()));

    graph_geant->SetPoint     (bin,minE+bin*maxE/1000., SP);
    graph_geant->SetPointError(bin,0, prof->GetRMS()/sqrt(prof->GetEntries()));
    		    
  }



  // Plot

  TCanvas *c1 = new TCanvas("c1","Radon",1400,600);
  c1->Divide(2,1);

  c1->cd(1);
  gPad->SetLogx();
  dEdxvsE->GetYaxis()->SetTitle("dE/dX [MeV/cm]");
  dEdxvsE->GetXaxis()->SetTitle("Kinetic energy [MeV]");
  dEdxvsE->Draw("colz");

  dEdxvsE_histo->SetMarkerColor(0);
  dEdxvsE_histo->SetMarkerStyle(4);
  dEdxvsE_histo->Draw("histPsame");

  graph_estar->SetMarkerStyle(2);  //cross
  graph_estar->Draw("Psame");


  c1->cd(2);
  gPad->SetLogx();
  graph_geant->SetMarkerColor(2);
  graph_geant->SetMarkerStyle(20);
  graph_geant->SetTitle("Mass stopping power");
  graph_geant->GetYaxis()->SetTitle("dE/#rhodX [MeVcm^{2}/g]");
  graph_geant->GetXaxis()->SetTitle("Kinetic energy [MeV]");
  graph_geant->Draw("AP");

  graph_estar->SetMarkerStyle(2);
  graph_estar->Draw("Psame");


  c1->SaveAs(output);
  //  system("display "+(std::string)output);

  
  return 0;

}
