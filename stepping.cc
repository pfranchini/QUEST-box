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
  if (edep != .0){
    
    G4Track *track = step->GetTrack();
    G4int pid = track->GetParticleDefinition()->GetPDGEncoding();
    G4double length = step->GetStepLength();
    
    // Add energy deposition to the total
    fEventAction->AddEdep(track->GetTrackID(),edep);

    // Add step length to the total
    fEventAction->AddLength(track->GetTrackID(),length);
    
    // PDG ID
    fEventAction->SetPDG(track->GetTrackID(),pid);

    //    G4cout << edep << " - " << length << G4endl;
    
    /*    if (pid == 22) {
      G4cout << "Step energy in " << fScoringVolume->GetName() << ": " << edep << G4endl;
      G4cout << "PID: " << track->GetParticleDefinition()->GetParticleName() << G4endl;
      G4cout << "     " << pid << G4endl; }*/
    
  }
  
}



