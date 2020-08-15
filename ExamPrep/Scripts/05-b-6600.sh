#!/bin/bash


# must not have same name
# compare file names and pick the smallest file

if [ $# -ne 1 ]; then
	echo "Invalid arguments" 
	exit 1 
fi

if [ -d $1 ]; then
	FILES=$(find $1 -type f 2>/dev/null -printf "%p\n")
	
	COUNT=$(echo "$FILES" | wc -l)

	for(( i=1;i<=$COUNT;i++ )); do 
		LINE="$(echo "$FILES" | head -n $i | tail -n 1)"

		for((j=1;j<=$COUNT;j++)); do
			LINE2="$(echo "$FILES" | head -n $j | tail -n 1)"

			if [ "$LINE" != "$LINE2" ]; then
				if [ -z "$(diff $LINE $LINE2 2>/dev/null)" ]; then

					printf "$LINE \n $LINE2" | sort | tail -n 1 | xargs -I {} rm {} 2>/dev/null

				fi	
			fi
		done
		# Sort lexico delete eveything except head fail
	done
	
else 
	echo "Not directory"
	exit 2 
fi
	



