#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
  fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();  // the volume where the particle is inside

  // Get the detector volume from the Construction
  const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

  // Check if the particle is in our detector
  if(volume != fScoringVolume)
    return;

  // Verbosity for particles inside the detector volume
  extern Configuration config;
  if (config.GetVerbosity()) {
    G4cout << "Event: " << G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()
	   << " - parent: " << step->GetTrack()->GetParentID()
	   << " - track: " << std::setw(2) << step->GetTrack()->GetTrackID()
	   << " - PID: " << step->GetTrack()->GetParticleDefinition()->GetPDGEncoding()
	   << " - Energy [MeV]: "  << std::setw(8) << std::setfill(' ') << std::setprecision(2) << step->GetTotalEnergyDeposit()/MeV
	   << " - Length [m]: "  << std::setw(8) << std::setfill(' ') << std::setprecision(2) << step->GetStepLength()/m
	   << " - Total Energy [MeV]: "  << std::setw(8) << std::setfill(' ') << std::setprecision(2) << step->GetTrack()->GetTotalEnergy()/MeV;
    if (step->GetTrack()->GetCreatorProcess())
      G4cout << " - Creator: " << step->GetTrack()->GetCreatorProcess()->GetProcessName();
    if (step->GetPreStepPoint()->GetProcessDefinedStep())
      G4cout << " - Process: " << step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;
    else
      G4cout << G4endl;
  }


  G4double edep = step->GetTotalEnergyDeposit();
  if (edep > .0){
    
    G4Track *track = step->GetTrack();
    G4int pid = track->GetParticleDefinition()->GetPDGEncoding();
    G4double length = step->GetStepLength();
    G4double energy = step->GetTrack()->GetTotalEnergy();
    G4double k = step->GetTrack()->GetKineticEnergy();
    
    // Add energy deposition to the total
    fEventAction->AddEdep(track->GetTrackID(),edep);

    // Add step length to the total
    fEventAction->AddLength(track->GetTrackID(),length);
    
    // PDG ID
    fEventAction->SetPDG(track->GetTrackID(),pid);

    // Writes Stepping ntuple
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4int i = track->GetTrackID(); 

    // Fills the ntuple 1
    man->FillNtupleIColumn(1, 0, event);    // ntuple 1, colum 0: Event number
    man->FillNtupleIColumn(1, 1, i);        // ntuple 1, colum 1: Track number
    man->FillNtupleIColumn(1, 2, pid);      // ntuple 1, colum 2: PDG ID
    man->FillNtupleDColumn(1, 3, k+edep);   // ntuple 1, colum 3: Track kinetic energy before this step
    man->FillNtupleDColumn(1, 4, edep);     // ntuple 1, colum 4: Step energy deposition
    man->FillNtupleDColumn(1, 5, length);   // ntuple 1, colum 5: Step length
    
    // Fills the energy deposition process: compt, Rayl, eBrem, eIon, msc, ionIoni
    if (step->GetPreStepPoint()->GetProcessDefinedStep()) {
      G4int process = 99;
      if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "compt")    process = 0;
      if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Rayl")     process = 1;
      if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "eBrem")    process = 2;
      if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "eIoni")     process = 3;
      if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "msc")      process = 4;
      if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "ionIoni") process = 5;
      man->FillNtupleIColumn(1, 6, process);  // ntuple 1, colum 5: Energy deposition process
    }
     
    man->AddNtupleRow(1);   
  
  }
  
}



