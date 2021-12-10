#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

  // === MATERIALS ===

  // Vacuum-like
  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*g/mole;
  G4double density = 1.e-25*g/cm3;
  G4double temperature = 2.73*kelvin;
  G4double pressure = 3.e-18*pascal;
  G4Material* vacuum = new G4Material("vacuum", atomicNumber, massOfMole, density, kStateGas, temperature, pressure);

  G4Material *liquidHe4 = new G4Material("liquidHe4", 2., 4., 0.125*g/cm3, kStateLiquid, 4*kelvin, 3.e-18*pascal);
  //  G4Material *liquidHe3 = new G4Material("liquidHe3", 2., 3., 0.100*g/cm3, kStateLiquid, 150E-6*kelvin, 3.e-18*pascal);
  G4Material *liquidHe3 = new G4Material("liquidHe3", 2., 4., 0.100*g/cm3, kStateLiquid, 1*kelvin, 1.e-5*pascal);


  // World
  G4Box *solidWorld = new G4Box("solidWorld", 10*m ,10*m ,10*m ); // size of the volume
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld"); // logial volume: material
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);  // mother physics volume


  // === DETECTOR ===

  // LHe3 detector
  G4double lhe3detector_side = 10*m;
  G4VSolid *solidLhe3detector = new G4Box("solidLhe3detector",lhe3detector_side, lhe3detector_side, lhe3detector_side);
  logicLhe3detector = new G4LogicalVolume(solidLhe3detector, liquidHe3, "logicLhe3detector");
  G4VPhysicalVolume *physLhe3detector = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicLhe3detector, "physLhe3detector", logicWorld, false, 0, true);



  return physWorld;

}
