#include "generator.hh"
#include "sources.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{
  fParticleGun = new G4ParticleGun(1); // 1 primary particle per event
}


MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

  extern Configuration config; // instance already defined in main()

  G4String source = config.GetParticle();
  G4double energy = config.GetEnergy();
  G4double charge = config.GetCharge();

  G4String volume = config.GetVolume();

  G4ThreeVector mom;

  if (source == "gamma" || source == "electron" || source == "alpha"){

    G4int PDGid;
    if (source == "gamma") PDGid = 22;
    if (source == "electron") PDGid = 11;
    if (source == "alpha") PDGid = 1000020040;
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable(); 
    G4ParticleDefinition *particle = particleTable->FindParticle(PDGid);
    fParticleGun->SetParticleDefinition(particle);
    
    mom.set((double) rand()/(RAND_MAX)*2.-1.,(double) rand()/(RAND_MAX)*2.-1.,(double) rand()/(RAND_MAX)*2.-1.);  // isotropical particle direction

  }
  
  else {

    G4int Z = 0;
    G4int A = 0;

    if (source == "Ac228") { Ac228 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Bi214") { Bi214 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Co60")  { Co60  isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Cs137") { Cs137 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "K40")   { K40   isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Mn54")  { Mn54  isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Pb210") { Pb210 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Pb212") { Pb212 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Pb214") { Pb214 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Ra226") { Ra226 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Th234") { Th234 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Tl208") { Tl208 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "U235")  { U235  isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "U238")  { U238  isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "U234")  { U234  isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Th230") { Th230 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Rn226") { Rn226 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Po218") { Po218 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Po214") { Po214 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Bi210") { Bi210 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Po210") { Po210 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Th232") { Th232 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Th228") { Th228 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Ra224") { Ra224 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Rn220") { Rn220 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Po216") { Po216 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Bi212") { Bi212 isotope; Z = isotope.Z; A = isotope.A;}
    if (source == "Po212") { Po212 isotope; Z = isotope.Z; A = isotope.A;}

    energy = 0.*keV;
    mom.set(0.,0.,0.);

    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);
    if ( source != ion->GetParticleName()){
      G4cout << G4endl << "Wrong definition of the Ion, stopping here!" << G4endl << G4endl;
      return;
    }
    fParticleGun->SetParticleDefinition(ion);
  }

  if (!fParticleGun->GetParticleDefinition()) {
    G4cout << G4endl << "Wrong particle, stopping here!" << G4endl << G4endl;
    return;
  }


  // Generate a particle from the Origin (0,0,0):                                                                                                                        
  
  G4ThreeVector pos(0.,0.,0.);

  fParticleGun->SetParticleCharge(charge);
  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleEnergy(energy);
  
  // Tells G4 to generate the primary vertex                                                                                                                               
  fParticleGun->GeneratePrimaryVertex(anEvent);


  
}
