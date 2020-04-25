#!/bin/bash

RANDOM_NUMBER=$(( (RANDOM % 100) + 1 ))
NUMBER_TRIES=0
while :	
do
	read -p "Enter a number:" INPUT
	(( NUMBER_TRIES=NUMBER_TRIES+1 )) 
	
	if [ $INPUT -gt $RANDOM_NUMBER ]; then
		echo "Go lower" 
	elif [ $INPUT -lt $RANDOM_NUMBER ]; then
		echo "Go higher"
	else 
		echo "Correct! Number of guesses $NUMBER_TRIES"
		exit 0
	fi
done
