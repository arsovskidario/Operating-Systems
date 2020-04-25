#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments"
	exit 2
fi

SRC=$1
DST=$2

EXTENTIONS=$(find $SRC -type f -name "*.*" -printf "%f \n" 2>/dev/null |cut -d "." -f 2 | sort | uniq) 
for i in $EXTENTIONS
do
	mkdir -p $DST/$i	
	find $SRC -name "*.$i" -exec cp {} $DST/$i \; 2>/dev/null
done
