#!/bin/bash

read -p "Enter file and string: " FILE STR

if [ -e ${FILE} ]; then
	if [ -n "${STR}" ]; then
		cat $FILE | egrep -w "${STR}" 
		exit 0
	fi
fi

exit 1 
