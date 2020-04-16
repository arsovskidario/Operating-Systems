#!/bin/bash

if [ $# -eq 0 ] || [ $# -ge 3 ] ; then
	echo "Invalid arguments"
	exit 2 
fi

NUMBER=$1
DELIMETAR=$2

if [ $# -eq 1 ]; then
	DELIMETAR=' '
fi

for (( i=0; i<${#NUMBER};i++ )); do
	(( COUNTER=${#NUMBER} - i ))
	if [ $(( COUNTER % 3 )) -eq 1 ] && [ $i -ne $(( ${#NUMBER}-1 )) ]; then
		printf "${NUMBER:$i:1}${DELIMETAR}"
	else 
		printf "${NUMBER:$i:1}"
	fi

done

echo #adds a newline 
