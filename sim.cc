#include <iostream>

//#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "configuration.hh"

Configuration config;

static void show_usage()
{
  std::cerr << "Usage: ./sim <options>\n"
            << "Options:\n"
	    << "\t-p,--particle\t\tName of the particle source <gamma|Ac228|Bi214|Co60|Cs137|K40|Mn54|Pb210|Pb212|Pb214|Ra226|Th234|Tl208|U235>\n"
	    << "\t-e,--energy\t\tEnergy for a gamma source [keV]\n"
	    << "\t-n,--number\t\tNumber of events to generate\n"
            << "\t-o,--output\t\tOutput root file (default: output.root)\n"
	    << "\t-g,--gui\t\tGUI after the run\n"
	    << "\t-V,--verbose\t\tVerbose output\n"
	    << std::endl;
}

int main(int argc, char** argv)
{

  // Set configuration for the particle generator and for the physical radioactive volume (from the command line arguments)
  G4String particle="gamma";
  G4double energy=1.*MeV; // MeV is the default unit in any case
  G4double charge=0.;

  G4String volume = "Cell";

  G4int numberOfEvents = 10;

  // Set configuration for the output ROOT file
  G4String output ="output.root";

  // Set configuration for the visualization
  G4bool gui = false;

  // Set verbosity
  G4bool verbosity = false;

  // Parse the command line
  std::string input;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if ((arg == "-h") || (arg == "--help")) {
      show_usage();
      return 0;
    }
    if ((arg == "-p") || (arg == "--particle"))
      particle = argv[i+1];
    if ((arg == "-e") || (arg == "--energy"))
      energy = atof(argv[i+1]);
    if ((arg == "-v") || (arg == "--volume"))
      volume = argv[i+1];
    if ((arg == "-n") || (arg == "--number"))
      numberOfEvents = atof(argv[i+1]);
    if ((arg == "-o") || (arg == "--output"))
      output = argv[i+1];
    if ((arg == "-g") || (arg == "--gui"))
      gui = true;
    if ((arg == "-V") || (arg == "--verbosity"))
      verbosity = true;
  }

  config.SetParticle(particle);
  config.SetEnergy(energy*keV); // uses keV
  config.SetCharge(charge);
  config.SetVolume("phys"+volume);
  config.SetEvents(numberOfEvents);
  config.SetOutput(output);
  config.SetVerbosity(verbosity);

  // Print the current configuration
  G4cout << "**************************************************************" << G4endl;
  G4cout << "Source:           " << particle << G4endl;
  G4cout << "Energy [keV]:     " << energy << G4endl;
  G4cout << "Volume:           " << volume << G4endl;
  G4cout << "Number of events: " << numberOfEvents << G4endl;
  G4cout << "Output file       " << output << G4endl;

  // G4 Run Manager
  G4RunManager *runManager = new G4RunManager;
  runManager->SetUserInitialization(new MyDetectorConstruction());  // detector geometry
  runManager->SetUserInitialization(new MyPhysicsList());           // physics process
  runManager->SetUserInitialization(new MyActionInitialization());  // primary particle
  
  runManager->Initialize();

  // UI
  G4UIExecutive *ui = new G4UIExecutive(argc, argv);

  // Visualization
  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();
  
  // UI Manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if (gui) UImanager->ApplyCommand("/control/execute ../vis.mac");

  G4cout << "\n ==== Start of the run ==== \n" << G4endl;

  //UImanager->ApplyCommand("/control/execute ../gen.mac");
  runManager->BeamOn(numberOfEvents);

  if (gui) ui->SessionStart();

  G4cout << "\n ==== End of the session ==== \n" << G4endl;


  // job termination
  delete runManager;

  return 0;
  
}

