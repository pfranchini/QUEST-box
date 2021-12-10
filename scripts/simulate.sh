
for energy in {1..10..1}; do
    echo "Energy [keV]: $energy"

echo "./sim -p electron -e $energy -v Cell -n 10000 -o output_e$energy.root > /dev/null"
./sim -p electron -e $energy -v Cell -n 10000 -o output_e$energy.root > /dev/null
#echo "/home/pfranchi/QUEST/plot/plot -i output_e$energy.root -o plot$energy.png"

done
