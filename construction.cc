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

  // Air
  G4Material *air = nist->FindOrBuildMaterial("G4_AIR");

  // Concrete
  G4Material* concrete = new G4Material("concrete", 2.5*g/cm3, 6);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_O"), 0.52);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Si"), 0.325);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Ca"), 0.06);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Na"), 0.015);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Fe"), 0.04);
  concrete->AddMaterial(nist->FindOrBuildMaterial("G4_Al"), 0.04);

  // Aluminium alloy 6061
  G4Element* elementMg = new G4Element("Magnesium", "Mg",12., 24.3050*g/mole);
  G4Element* elementAl = new G4Element("Aluminium", "Al",13., 26.9815*g/mole);   
  G4Element* elementSi = new G4Element("Silicon",   "Si",14., 28.0855*g/mole);
  G4Element* elementFe = new G4Element("Iron",      "Fe",26.,  55.845*g/mole);   
  G4Material *Al6061 = new G4Material("Al6061", 2.70*g/cm3, 4);
  Al6061->AddElement(elementAl, 0.980);
  Al6061->AddElement(elementMg, 0.010); 
  Al6061->AddElement(elementSi, 0.006);
  Al6061->AddElement(elementFe, 0.004);

  G4Material *StainlessSteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  //G4Material *Brass = nist->FindOrBuildMaterial("G4_BRASS");
  G4Material *SI = nist->FindOrBuildMaterial("G4_POLYETHYLENE");  // super insulation (metallization not considered)
  G4Material *liquidNitrogen = new G4Material("liquidNitrogen", 7., 14.01*g/mole, 0.808*g/cm3, kStateLiquid, 77*kelvin);
  G4Material *liquidHe4 = new G4Material("liquidHe4", 2., 4., 0.125*g/cm3, kStateLiquid, 4*kelvin, 3.e-18*pascal);
  G4Material *liquidHe3 = new G4Material("liquidHe3", 2., 3., 0.100*g/cm3, kStateLiquid, 150E-6*kelvin, 3.e-18*pascal);

  // Epoxy with density of Stycast 1266 - TO BE CHECKED the molecular formula of Stycast
  G4Material* Epoxy = new G4Material("Epoxy", 1.12*g/cm3, 3, kStateSolid, 1*kelvin);
  Epoxy->AddElement(nist->FindOrBuildElement("C"), 11);
  Epoxy->AddElement(nist->FindOrBuildElement("H"), 12);
  Epoxy->AddElement(nist->FindOrBuildElement("O"), 3);


  // === CRYOSTAT ELEMENTS ===  based on https://docs.google.com/spreadsheets/d/1e7HkvcitA5hH9ebrBamfAdSRf9U9PjKW34qNZhv5iso

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


/*void MyDetectorConstruction::ConstructSDandField()
{

  /*  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  if(logicLhe3detector != NULL)
    logicLhe3detector->SetSensitiveDetector(sensDet);
  
}
*/
