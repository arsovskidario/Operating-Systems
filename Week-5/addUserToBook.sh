#!/bin/bash

if [ $# -ne 4 ]; then
	echo "Invalid arguments"
	exit 2
fi

FILENAME="$1"
FULL_NAME="$2 $3"
USER_NAME="$4"

COUNT_USER=$(grep -w "${FULL_NAME}" passwd.txt | wc -l)
if [ $COUNT_USER -eq 0 ]; then
	echo "No user found " 
fi	

if [ $COUNT_USER -eq 1 ]; then
	USER_ID=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f 1)
else
	USER_NAMES=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f 1)
	COUNTER=0
	echo " SELECT YOUR USERNAME "
	for item in $USER_NAMES; do
		((COUNTER =COUNTER+1))
		echo "$COUNTER. $item" 
	done			
	read SELECTED_NUMBER
	USER_ID=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f 1 | head -$SELECTED_NUMBER | tail -n 1)
fi

echo "${USER_NAME} ${USER_ID}" >> phoneBook
 
