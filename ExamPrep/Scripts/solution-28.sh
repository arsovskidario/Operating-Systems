#!/bin/bash

#read  INPUT

INPUT=$(cat numbers.txt)

NUMBERS=$(echo "$INPUT" | sort | uniq |  egrep "^\-?[0-9\.]+$")

MAX_ABSOLUTE=0
while read line
do
	ABSOLUTE=$(echo "$line" | sed 's/^\-//')

	if [ $ABSOLUTE -gt $MAX_ABSOLUTE ]; then
		MAX_ABSOLUTE=$ABSOLUTE
	fi

done < <(echo -e "$NUMBERS")


while read line
do
	if [ $(echo "$line" | sed 's/^\-//') -eq $MAX_ABSOLUTE ]; then
		echo "$line"
	fi
done < <(echo -e "$NUMBERS")
