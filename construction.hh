#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "Randomize.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {  // class derived from G4VUserDetectorConstruction


public:

  MyDetectorConstruction();
  ~MyDetectorConstruction();

  G4LogicalVolume *GetScoringVolume() const { return logicBox; }
  
  virtual G4VPhysicalVolume *Construct();


private:

  G4LogicalVolume *logicBox;
  //  virtual void ConstructSDandField();  // Sensitive Detectors (and Field)

  
};


#endif
