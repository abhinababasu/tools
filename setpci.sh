#!/bin/sh
device="82599ES"
value="0x0009"

for i in `lspci | grep $device | awk '{ print $1}'`; do
    currval=`setpci -s $i 0xC8.w`
    `setpci -s $i 0xC8.w=$value`
    newval=`setpci -s $i 0xC8.w`
    echo "PCI Slot $i Set from $currval to $newval"
    grep -q -F "$i" /etc/init.d/boot.local || echo "setpci -s $i 0xC8.w=$value" >> /etc/init.d/boot.local
done
