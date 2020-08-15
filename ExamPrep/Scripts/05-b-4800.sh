#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments"
	exit 1
fi


if [ -d $2 ]; then
	if [ -f $1 ]; then
		RESULT=$(find $2 -type f -printf "%p\n" 2>/dev/null)

		NUMBER_LINES=$( echo "$RESULT" | wc -l) 
		
		for((i=1;i<$NUMBER_LINES;i++)); do
			LINE=$(echo "$RESULT" | head -n $i | tail -n 1)
			
			if [ -z "$(diff $LINE $1)" ]; then
				echo "$LINE"
			fi

		done

	fi
fi
