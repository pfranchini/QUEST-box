#include "run.hh"


MyRunAction::MyRunAction()
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("Scoring", "Scoring"); // ntuple 0 
  man->CreateNtupleIColumn("fEvent");      // Event number
  man->CreateNtupleIColumn("fTrack");      // Track number
  man->CreateNtupleIColumn("fPDG");        // PDG ID
  man->CreateNtupleDColumn("fEdep");       // Energy deposition
  man->CreateNtupleDColumn("fLength");     // Track length
  man->FinishNtuple(0);                    // ntuple 0

}

MyRunAction::~MyRunAction()
{}


void MyRunAction::BeginOfRunAction(const G4Run* run)
{

  extern Configuration config;  // instance already defined in main()    

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  //  G4int runID = run->GetRunID();
  //  G4cout << "Run: " << runID << G4endl;
  //  std::stringstream strRunID;
  //  strRunID << runID;
  //  man->OpenFile("output"+strRunID.str()+".root") */;

  man->OpenFile(config.GetOutput());

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile();

}
