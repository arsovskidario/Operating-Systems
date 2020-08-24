#!/bin/bash

if [ $# -ne 1 ];then
	echo "Invalid arguments"
	exit 1
fi


if [ -d $1 ];then

	FRIENDS=$(find $1 -mindepth 3 -maxdepth 3 -printf "%p\n")
	NAMES=$(echo "$FRIENDS" | egrep -o "/[a-zA-Z0-9]+$" | tr -d "/" | sort | uniq)

	while read line;
	do

		# First find directory and that cat the directory 

		MATCHES=$(echo $FRIENDS | egrep "$line" )

		RESULT=0
		for i in "$MATCHES";
		do
			NEW_RESULT=$(find "$i" -type f 2>/dev/null | egrep "[0-9]{4}\-[0-9]{2}\-[0-9]{2}\-[0-9]{2}\-[0-9]{2}\-[0-9]{2}.txt" | xargs -I {} -n 1 wc -l {} | cut -d " " -f 1)
			if [ -n "$NEW_RESULT" ];then
				((RESULT+=$NEW_RESULT))
			fi
		done


		echo "$line $RESULT" > result.txt

	done < <(echo -e "$NAMES")


	cat result.txt | sort -nrk 2 | head -n 10 


fi
