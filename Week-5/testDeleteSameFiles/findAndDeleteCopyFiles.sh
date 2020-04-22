#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid arguments "
	exit 2
fi

SRC_DIR=$1

FILES=$(find $SRC_DIR -type f 2>/dev/null | sort )

# Strings array and find for every string cmp files if found copy and different name delete it 
COUNTER=0
for i in $FILES :
do 
        for j in $FILES :
	do
		if [ $i != $j ]; then
			cmp $i $j  > /dev/null 2>&1 
				if [ $? -eq 0 ]; then
					rm $j
				fi 
		fi 
	done

done
