#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "G4String.hh"

class Configuration {

private:
  
  G4String fParticle;
  G4double fEnergy;
  G4double fCharge;

  G4int fEvents;

  G4String fVolume;

  G4String fOutput;

  G4bool fVerbosity;

public:
  
  Configuration() {};
  ~Configuration() {};

  // Setters and Getters for the particle generator configuration and the irradiate volume
  void SetParticle(G4String particle) { fParticle = particle; };
  G4String GetParticle() const { return fParticle; };

  void SetEnergy(G4double energy) { fEnergy = energy; };
  G4double GetEnergy() const { return fEnergy; }

  void SetCharge(G4double charge) { fCharge = charge; };
  G4double GetCharge() const { return fCharge; }

  void SetVolume(G4String volume) { fVolume = volume; };
  G4String GetVolume() const { return fVolume; };

  // Number of events to be generated
  void SetEvents(G4double events) { fEvents = events; };
  G4double GetEvents() const { return fEvents; }
  
  // Output ROOT file
  void SetOutput(G4String output) { fOutput = output; };
  G4String GetOutput() const { return fOutput; };

  // Verbosity
  void SetVerbosity(G4bool verbosity) { fVerbosity = verbosity; };
  G4bool GetVerbosity() const { return fVerbosity; };

};


#endif

