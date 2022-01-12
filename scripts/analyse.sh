

where="/home/pfranchi/QUEST/QUEST-box/scripts/output"

dir=`pwd`

cd $where

rm -f output.log
rm -f result
rm -f plot*.png

for file in output_e*.root; do

    echo $file
    energy=`echo $file | sed -e 's/output_e\(.*\).root/\1/'`

    echo "Energy [keV]:" $energy

    echo "/home/pfranchi/QUEST/QUEST-box/plot/plot -i $file -o plot$energy.png"
    /home/pfranchi/QUEST/QUEST-box/plot/plot -i $file -o $where/plot$energy.png > $dir/output.log
    s=`grep "Stopping power" $dir/output.log | awk {'print $3'}`
    echo $energy " " $s >> $dir/result

done

rm -f $dir/output.log
cd $dir
