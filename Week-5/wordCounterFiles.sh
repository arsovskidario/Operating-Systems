#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid arguments"
	exit 2 
fi

for i in $@ 
do 
	echo "$i number lines : $(wc -l $i | cut -d " " -f 1 )"
done
