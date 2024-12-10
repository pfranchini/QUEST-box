# Run a set of simulation for electrons using a range of energies [1-1000 keV]:
# Usage: ./simulate.sh

exe="/home/pfranchi/QUEST/QUEST-box/build/sim"

for energy in {1..1000..10}; do
    echo "Energy [keV]: $energy"
    echo "$exe -p electron -e $energy -v Cell -n 10000 -o output/output_e$energy.root > /dev/null"
    $exe -p electron -e $energy -v Cell -n 10000 -o output/output_e$energy.root > /dev/null
done
