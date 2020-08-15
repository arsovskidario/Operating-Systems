#!/bin/bash

#read  INPUT

INPUT=$(cat numbers.txt)

NUMBERS=$(echo "$INPUT" | sort | uniq |  egrep "^\-?[0-9\.]+$")

RESULT=$(mktemp)

while read line
do

	EXPR=$(echo $line |sed -E 's/(\-|\.)//' | sed -E 's/(.)/1+/g' | sed -E 's/.$//') 

	SUM=$(( $EXPR ))

	echo "$line" "$SUM" >> "${RESULT}"

done < <(echo -e "$NUMBERS")

MAX_SUM=$(cat "${RESULT}" | sort -nrk 2 |head -n 1 | awk '{print $2}') 


cat "${RESULT}" | egrep "\s$MAX_SUM$" | sort -nk 1 | head -n 1 | cut -d " " -f 1   
