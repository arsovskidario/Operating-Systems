#!/bin/bash
if [ $# -le 0 ]; then
	echo " invalid arguments" 
	exit 1
fi

FILE="$1" 
NAME="$2"

echo "User's ID : $(grep -w "$NAME" $FILE | cut -d " " -f 2)"
