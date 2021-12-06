#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Proton.hh"
#include "G4VSolid.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4IonTable.hh"

#include "construction.hh"
#include "configuration.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{

public:
  MyPrimaryGenerator();
  ~MyPrimaryGenerator();
    
  virtual void GeneratePrimaries(G4Event*); // creating the primaries to be used by the action
    
private:
  G4ParticleGun *fParticleGun;  // particle gun

};

#endif
