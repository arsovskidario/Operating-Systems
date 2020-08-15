#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Invalid number of arguments"
	exit 1
fi

if [[ "$1" =~ ^-?[0-9]*$ && "$2" =~ ^-?[0-9]*$ && "$3" =~ ^-?[0-9]*$ ]]; then
	if [[ $1 -ge $2 && $1 -le $3 ]]; then
		exit 0
	elif [[ $1 -le $2 && $1 -ge $3 ]]; then
                exit 2
 	else
		exit 1
	fi

else
	exit 3 
fi       
