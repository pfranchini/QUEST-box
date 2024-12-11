#include "event.hh"


MyEventAction::MyEventAction(MyRunAction*)
{

  fill(fPDG.begin(), fPDG.end(), 0);
  fill(fEdep.begin(), fEdep.end(), 0.);
  fill(fLength.begin(), fLength.end(), 0.);

}


MyEventAction::~MyEventAction()
{}


void MyEventAction::BeginOfEventAction(const G4Event*)
{
  // Initialize the energy deposition for each new event
  fill(fEdep.begin(), fEdep.end(), 0.);
  // Initialize the PDG list for each new event
  fill(fPDG.begin(), fPDG.end(), 0);
  fill(fLength.begin(), fLength.end(), 0.);

  // Print some event numbers
  G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  if (event <= 10)  G4cout << "Event: " << event << G4endl;
  if (event > 10 && event <=100)     if (event%10==0)  G4cout << "Event: " << event << G4endl;
  if (event > 100 && event <=1000)   if (event%100==0)  G4cout << "Event: " << event << G4endl;
  if (event > 1000 && event <=10000) if (event%1000==0)  G4cout << "Event: " << event << G4endl;
  if (event > 10000)                 if (event%10000==0)  G4cout << "Event: " << event << G4endl;
  
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
  
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // Fill the ntuple at the end of the Event
  // Loops over the tracks of this Event
  for ( std::vector<int>::size_type i = 0; i < fPDG.size(); ++i ) 
    if (fEdep[i] > 0.){

      man->FillNtupleIColumn(0, 0, event);      // ntuple 0, colum 0: Event number
      man->FillNtupleIColumn(0, 1, i);          // ntuple 0, colum 1: Track number
      man->FillNtupleIColumn(0, 2, fPDG[i]);    // ntuple 0, colum 2: PDG ID
      man->FillNtupleDColumn(0, 3, fEdep[i]);   // ntuple 0, colum 3: Energy deposition
      man->FillNtupleDColumn(0, 4, fLength[i]); // ntuple 0, colum 4: Total track length
      man->AddNtupleRow(0);                     // ntuple 0
    
   }
}
