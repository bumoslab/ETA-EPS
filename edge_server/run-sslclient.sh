#!/bin/bash
memory=20
name="server-"
# input="25-1.dat"

for i in $(seq $1 $2);
do
    #netmask (ip/16) should be set up correctly
    sudo /home/moslab/Desktop/unikernel/rumprun/rumprun/bin/rumprun xen -i -I newnet,xenif,bridge=xenbr0,mac=00:16:3a:00:00:00 -W newnet,inet,static,10.32.135.12/16 -M 20 -N "$name-$i" -- edge.bin 10.32.140.235 4433
    # sudo /home/moslab/Desktop/unikernel/rumprun/rumprun/bin/rumprun xen -i  -M 20 -N "$name-$i" -- server.bin 0.0.0.0 8080
# sudo /home/moslab/Desktop/unikernel/rumprun/rumprun/bin/rumprun xen -i -I newnet,xenif -W newnet,inet,dhcp -M 20 -- server.bin 0.0.0.0 8080

    # sudo ~/Desktop/unikernel/rumprun/rumprun/bin/rumprun xen -i -M $memory -N "$name-$i"  -b hdd.img,/data -- myexample.bin
    # sleep 4
    # echo $i
done
