#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments" 
	exit 1
fi

if [ -d $1 ]; then
	if [[ $2 =~ ^[0-9]*$ ]]; then
		find $1 -type f -size +$2c 2>/dev/null -printf "%p\n"
	else

		echo "Not a number" 
		exit 3
	fi
else
	echo "Directory doesn't exist"
	exit 2
fi   	
