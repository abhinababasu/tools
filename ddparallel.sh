#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Specify the number of cores"
    exit 1
fi

for i in $(seq 1 $1)
do
    echo "running $i"
    `taskset -c $i dd if=/dev/zero of=/hana/logbackups/$i.txt bs=1G count=4 oflag=direct 1>~/$i.txt 2>&1 &`
done
