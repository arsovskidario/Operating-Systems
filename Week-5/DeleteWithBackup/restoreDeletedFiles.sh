#!/bin/bash

SRC_BACK=/home/dario/Development/Operating-Systems/Week-5/DeleteWithBackup/backup
if [ "$1" == "-l" ];then
	ls $SRC_BACK | awk -F "_" '{printf "%s (%s-%s)\n",$1,$2,$3}' | sed 's/.tar//' 
	exit 1
fi

# Add a way to select the name 
FULL_NAME="$(ls $SRC_BACK | grep -e "$1")"

NUMBER_MATCHES=$(ls $SRC_BACK | grep -e "$1" | wc -l)

if [ $NUMBER_MATCHES -ne 1 ]; then
	POSITION=1
	for i in $FULL_NAME
	do	
		echo "($POSITION) $i"
		((POSITION+=1))
	done
	
	read -p "enter position " row
	FULL_NAME="$(ls $SRC_BACK | grep -e "$1" | head -n $row | tail -n 1)"
fi

SRC="$SRC_BACK/$FULL_NAME"
DEST="$(pwd)"

if [ $# -eq 2 ]; then
	DEST="$2"	
fi

tar -xf $SRC --directory $DEST
