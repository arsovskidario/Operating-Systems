#!/bin/bash
if [ $# -lt 3 ]; then
	echo "Invalid arguments"
fi

NUMBER=$1
START=$2
END=$3

# Check arguments for integer values 
printf "'$*'" | grep -w "[0-9]*\s[0-9]*\s[0-9]*" >/dev/null

# If any argument is different from integer exit status 3
if [ $? -eq 1 ]; then
	exit 3
fi

if [ $2 -gt $3 ] ; then
	exit 2
fi

if [ $1 -gt $2 ] && [ $1 -lt $3 ] ; then
	exit 0
else
	exit 1
fi

#Script kiddie material right here 
