# Box of LHe3

Simulation of the LHe3 detector using Geant4, to study the energy deposition in a larger volume, than the QUEST-DMC detector one.

 - Box filled with LHe3
 - Particle generator from the centre of the box
 - Generators: a particle (`G4ParticleTable`) or a radioactive isotope (`G4IonTable`) from a defined list
 - Energy deposition in the LHe3 detector volume

 - Output: Root ntuples (`| Event number | Track number | PDG ID | Total energy deposition [MeV] | Track length [mm] |`)
[to be updated...]
 - Configuration from command line arguments

```
git clone git@github.com:pfranchini/QUEST-box
```
or to fetch changes
```
git pull
```
[source Geant4 environment]
```
mkdir build; cd build
cmake ../
make

Usage: ./sim <options>
Options:
        -p,--particle           Name of the particle source <gamma|Ac228|Bi214|Co60|Cs137|K40|Mn54|Pb210|Pb212|Pb214|Ra226|Th234|Tl208|U235>
        -e,--energy             Energy for a gamma source [keV]
        -n,--number             Number of events to generate
        -o,--output             Output root file (default: output.root)
        -g,--gui                GUI after the run
```
Examples:
Generates 10000 electrons of 10 MeV from the centre of the box, stored in `he3_10MeV_Livermore.root`:
```
./sim -p electron -e 10000 -n 10000 -o he4_10MeV_Livermore.root
```

Generates 10 photons of 1.2 keV from the centre of the box, stored in `output.root` and visualized in the Geant4 UI:
```
./sim -p gamma -e 1.2 -n 10 -o output.root -g
```

Generates 1000 events from the K-40 isotope coming from the centre of the box, stored in `output_Th234.root`:
```
./sim -p K40 -n 1000 -o output_Th234.root
```

## Plot
```
cd plot
./steps -i ../build/he3_10MeV_Livermore.root -d 0.100 -o test.png -m ../scripts/estar_He3
```

## Simulation (legacy)

Run a set of simulation for electrons using a range of energies
```
cd scripts
./simulate.sh
```
output: `output/output_e[energy].root`
```
./analyse.sh
```
python plot.py


## Geant4 environment via CVMFS for AlmaLinux 9.4 (geant4 v11.2):

```
source /cvmfs/sft.cern.ch/lcg/contrib/gcc/11/x86_64-el9-gcc11-opt/setup.sh
source /cvmfs/geant4.cern.ch/geant4/11.2/x86_64-el9-gcc11-optdeb/bin/geant4.sh
source /cvmfs/geant4.cern.ch/geant4/11.2/x86_64-el9-gcc11-optdeb-MT/CMake-setup.sh
export PATH=/cvmfs/sft.cern.ch/lcg/contrib/CMake/3.18.3/Linux-x86_64/bin/:${PATH}
```

## Geant4 environment at RHUL (geant4 v10.7):

```
source /cvmfs/geant4.cern.ch/geant4/10.7/x86_64-centos7-gcc8-optdeb/bin/geant4.sh
source /cvmfs/sft.cern.ch/lcg/contrib/gcc/8/x86_64-centos7/setup.sh
source /cvmfs/sft.cern.ch/lcg/releases/LCG_100/qt5/5.12.4/x86_64-centos7-gcc9-opt/Qt5-env.sh
export PATH=/cvmfs/sft.cern.ch/lcg/contrib/CMake/3.18.3/Linux-x86_64/bin/:${PATH}
```
