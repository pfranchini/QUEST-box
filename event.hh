#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

#include "g4root.hh"

#include "run.hh"

class MyEventAction : public G4UserEventAction
{

public:

  MyEventAction(MyRunAction*);
  ~MyEventAction();
    
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
    
  void AddEdep(G4int track, G4double edep) { fEdep[track] += edep; } //; G4cout << fEdep[track] << G4endl;} 
  void AddLength(G4int track, G4double length) { fLength[track] += length; } //G4cout << fLength[track] << G4endl;}

  void SetPDG(G4int track, G4int pdg) { fPDG[track] = pdg; }


private:

  // An event can have multiple tracks, each stored separetely
  std::vector<G4int> fPDG = std::vector<G4int>(10000);
  std::vector<G4double> fEdep = std::vector<G4double>(10000);
  std::vector<G4double> fLength = std::vector<G4double>(10000);
  
  //G4int fPDG;
  //G4double fEdep;

};

#endif
