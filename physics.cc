#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{

  RegisterPhysics(new G4EmStandardPhysics());  // EM physics processes
  //RegisterPhysics(new G4EmLowEPPhysics());  // EM physics processes
  //RegisterPhysics(new G4EmLivermorePhysics());  // EM physics processes
  //RegisterPhysics(new G4EmPenelopePhysics());  // EM physics processes

  //RegisterPhysics(new G4OpticalPhysics());
  //  RegisterPhysics(new G4DecayPhysics());  // decays of "stable" particles
  //  RegisterPhysics(new G4RadioactiveDecayPhysics());  // decays of isotopes   
}

MyPhysicsList::~MyPhysicsList()
{}

