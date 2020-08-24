#!/bin/bash

read -p "Enter phoneBook and user " FILE USER

if [ -e $FILE ]; then
	if [ -n $USER ]; then

		cat $FILE | egrep "$USER" | cut -d " " -f 2 | xargs -I{} write {}  
		exit 0 
	fi 
fi

exit 1
