#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Invalid arguments" 
	exit 1
fi 

SRC=$1
FULL_NAME=$2
NICKNAME=$3

if [ -e $SRC ]; then
	
	if [ -n "$FULL_NAME" ]; then
		# USER_MATCH = $(cat ./passwd.txt | egrep "$FULL_NAME")
		# if[ (wc -l "${USER_MATCH}") -ne 1 ]; then
		# for(( i=1;i<$(wc -l "${USER_MATCH}";i++)); do
		# 	echo "$i $(head -n $i "${USER_MATCH}"| tail -n 1)"
		# done	
		# read -n "Choose username" CHOICE
		# if [ $CHOICE -eq 0 ];then
		#	echo "Okay bye"
		# else 
		# 	RESULT=head -n $CHOICE "${USER_MATCH}" |tail -n1 | cut -d ":" -f 1
		# 	echo "$NICKNAME $RESULT" >> $SRC
		# fi 
		#
		# fi 
		USERID=$(cat ./passwd.txt | egrep "$FULL_NAME" | cut -d ":" -f 1)

		    if [ -n "$USERID" ]; then
			echo "${NICKNAME} ${USERID}" >> $SRC
			exit 0
		    else
			    echo "No match found for full name"
			    exit 2
		    fi

	fi
fi
