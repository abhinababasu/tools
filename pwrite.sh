#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Specify the number of cores"
    exit 1
fi

for i in $(seq 1 $1)
do
    echo "running $i"
    `taskset -c $i ./writefile.exe /hana/logbackups/$i.txt 20 1>~/$i.txt 2>&1 &`
done
