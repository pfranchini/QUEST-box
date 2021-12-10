
rm -f output.log
rm -f result
rm -f plot*.png

where="/home/pfranchi/QUEST/box/build"

dir=`pwd`

cd $where

for file in output_e*.root; do

    echo $file
    energy=`echo $file | sed -e 's/output_e\(.*\).root/\1/'`

    echo "Energy [keV]:" $energy

    echo "/home/pfranchi/QUEST/plot/plot -i $file -o plot$energy.png"
    /home/pfranchi/QUEST/plot/plot -i $file -o $dir/plot$energy.png > $dir/output.log
    s=`grep "Stopping power" $dir/output.log | awk {'print $3'}`
    echo $energy " " $s >> $dir/result

done

cd $dire
