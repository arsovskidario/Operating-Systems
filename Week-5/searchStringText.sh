#!/bin/bash

read -p "Enter file and string for search " FILENAME STRING

echo $FILENAME, $STRING

# Turn off dev/null if you want the found text to appear 
grep -w "${STRING}" ${FILENAME} > /dev/null


if [ $? -eq 0 ]; then
	echo "Found string"
	exit 0
else
	echo "Not found" 
	exit 1
fi

