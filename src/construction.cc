#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

  // === MATERIALS ===

  G4NistManager *nist = G4NistManager::Instance();

  // Vacuum-like
  G4double atomicNumber = 1.;
  G4double massOfMole = 1.008*g/mole;
  G4double density = 1.e-25*g/cm3;
  G4double temperature = 2.73*kelvin;
  G4double pressure = 3.e-18*pascal;
  G4Material* vacuum = new G4Material("vacuum", atomicNumber, massOfMole, density, kStateGas, temperature, pressure);

  // Already validated: 

  G4Material *liquidHe4 = new G4Material("liquidHe4", 2., 4., 0.125*g/cm3, kStateLiquid, 4*kelvin, 3.e-18*pascal);
  //G4Material *liquidHe4 = new G4Material("liquidHe4", 2., 4., 0.0001786*g/cm3); //, kStateLiquid, 4*kelvin, 3.e-18*pascal);
  //G4Material *liquidHe4 = new G4Material("liquidHe4", 2., 4., 0.100*g/cm3); //, kStateLiquid, 4*kelvin, 3.e-18*pascal);
  //G4Material *liquidHe3 = new G4Material("liquidHe3", 2., 3., 0.100*g/cm3, kStateLiquid, 150E-6*kelvin, 3.e-18*pascal);
  G4Material *liquidHe3 = new G4Material("liquidHe3", 2., 4., 0.100*g/cm3); //, kStateLiquid, 1*kelvin, 1.e-5*pascal);


  // Cryostat materials to be tested:

  // Concrete: concrete
  G4Material* concrete = new G4Material("concrete", 2.5*g/cm3, 6);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_O"), 0.52);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Si"), 0.325);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Ca"), 0.06);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Na"), 0.015);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Fe"), 0.04);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Al"), 0.04);

  // Aluminium alloy 6061: Al6061
  G4Element* elementMg = new G4Element("Magnesium", "Mg",12., 24.3050*g/mole);
  G4Element* elementAl = new G4Element("Aluminium", "Al",13., 26.9815*g/mole);   
  G4Element* elementSi = new G4Element("Silicon",   "Si",14., 28.0855*g/mole);
  G4Element* elementFe = new G4Element("Iron",      "Fe",26.,  55.845*g/mole);   
  G4Material *Al6061 = new G4Material("Al6061", 2.70*g/cm3, 4);
  Al6061->AddElement(elementAl, 0.980);
  Al6061->AddElement(elementMg, 0.010); 
  Al6061->AddElement(elementSi, 0.006);
  Al6061->AddElement(elementFe, 0.004);

  // super insulation (metallization not considered): SI (0.94 g/cm3)
  G4Material *SI = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

  // Stainless Steel: StainlessSteel (8.0 g/cm3)
  G4Material *StainlessSteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");


  // World
  G4Box *solidWorld = new G4Box("solidWorld", 10*m ,10*m ,10*m ); // size of the volume
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld"); // logial volume: material
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);  // mother physics volume


  // === DETECTOR ===

  // LHe3 detector
  G4double lhe3detector_side = 10*m;
  G4VSolid *solidBox = new G4Box("solidBox",lhe3detector_side, lhe3detector_side, lhe3detector_side);


  // SELECT MATERIAL OF THE BOX:
  logicBox = new G4LogicalVolume(solidBox, liquidHe3, "logicBox");
  //logicBox = new G4LogicalVolume(solidBox, liquidHe4, "logicBox");
  //logicBox = new G4LogicalVolume(solidBox, concrete, "logicBox");
  //logicBox = new G4LogicalVolume(solidBox, Al6061, "logicBox");
  //logicBox = new G4LogicalVolume(solidBox, SI, "logicBox");
  //logicBox = new G4LogicalVolume(solidBox, StainlessSteel, "logicBox");

  G4VPhysicalVolume *physBox = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicBox, "physBox", logicWorld, false, 0, true);



  return physWorld;

}
