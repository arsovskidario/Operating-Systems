#!/bin/bash


RESULT=$((RANDOM%100))

ATTEMPT=0
while : 
do

	read -p "Guess?" GUESS

	((ATTEMPT=ATTEMPT+1))

	if [ $GUESS -lt $RESULT ];then
		echo "Go bigger"
	elif [ $GUESS -gt $RESULT ]; then
		echo "Smaller"
	else 
		printf "Correct guess, attempted $ATTEMPT times \n"
		exit 0
	fi
done
