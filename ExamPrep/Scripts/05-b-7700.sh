#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments" 
	exit 1
fi

if [ -d $1 ]; then
	if [[ "$2" =~ ^[0-9]+$ ]];then
		find $1 -type f -size +$2c -printf "%s\n" 2>/dev/null | awk 'BEGIN{COUNT=0} {COUNT = COUNT + $1} END{ print COUNT}'
	else
		echo "Second argument isn't a number"
		exit 2
	fi
else
	echo "First argument isn't a directory"
	exit 3
fi
