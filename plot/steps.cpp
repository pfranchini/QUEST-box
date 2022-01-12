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

  ////////////////////////////

  float maxE = 10;  // [MeV]

  ////////////////////////////

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

  TH2F *dEdxvsE = new TH2F("dEdxvsE","dEdx vs Kinetic Energy",1000, 0., maxE, 100, 0.0001, 20.);
  TH1F *dEdxvsE_histo = new TH1F("dEdxvsE_histo","dEdx vs Kinetic Energy",1000, 0., maxE);

  TGraph* graph = new TGraph(dEdxvsE->GetNbinsX());
  TGraph* graph_estar = new TGraph("/home/pfranchi/QUEST/QUEST-box/scripts/estar", "%lg %lg %*lg %*lg");

  Double_t StoppingPower = 0;
  Int_t count = 0;

  Long64_t nentries = t1->GetEntries();
  std::cout << "Entries: " << nentries << std::endl;
  for (Long64_t i=0;i<nentries;i++) {
    t1->GetEntry(i);

    //if (PDG==11&&Edep>0&&Length>0&&Process==3) {
    
    // Select only primary electrons
    if (Track==1&&PDG==11&&Edep>0&&Length>0) {
      
      dEdxvsE->Fill(E,100*Edep/Length);

      count++;
      StoppingPower = StoppingPower + Edep/Length;
    }
  }
  
  // Output
  std::cout << "Stopping power: " << StoppingPower/count << std::endl;

  // Project to 1D histogram
  for ( Int_t bin = 1; bin < dEdxvsE->GetNbinsX(); bin++ ){
    TH1D *prof = dEdxvsE->ProjectionY("prof",bin,bin+1,"");
    dEdxvsE_histo->SetBinContent(bin,prof->GetMean());
    dEdxvsE_histo->SetBinError(  bin,prof->GetRMS()/sqrt(prof->GetEntries()));

    graph->SetPoint(bin,bin*maxE/1000.,prof->GetMean());
    //    std::cout << bin/100. << ": " << prof->GetMean() << std::endl;

		    
  }


  // ESTAR



  // Plot

  TCanvas *c1 = new TCanvas("c1","Radon",1400,600);
  c1->Divide(2,1);

  c1->cd(1);
  gPad->SetLogx();
  dEdxvsE->Draw("colz");

  /*  c1->cd(2);
  gPad->SetLogx();
  dEdxvsE_histo->Draw("E1");*/

  c1->cd(2);
  gPad->SetLogx();
  graph->SetMarkerColor(2);
  graph->SetMarkerStyle(20);
  graph->SetTitle("Mass stopping power");
  graph->GetYaxis()->SetTitle("dE/#rhodX [MeVcm^{2}/g]");
  graph->GetXaxis()->SetTitle("Kinetic energy [MeV]");
  graph->Draw("AP");

  graph_estar->SetMarkerStyle(2);
  graph_estar->Draw("Psame");


  c1->SaveAs(output);
  //system("display "+(std::string)output+"&");


  
  return 0;

}
