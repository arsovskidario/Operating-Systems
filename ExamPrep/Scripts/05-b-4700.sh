#!/bin/bash

if [ $# -lt 1 ]; then
	exit 1
fi

NUMBER=$1
DELIM=" "

if [ -n "$2" ]; then
	DELIM=$2
fi

i=0
flag=0
LEN=${#1}

if [ $(( $LEN%3 )) == 0 ]; then
	echo "In"
	flag=1	
fi

for ((;i<$LEN;i++)); do

	if [ $(( $(($LEN-i)) %3 )) == 0 ]; then
		if [[ $i -ne 0 && $flag -ne 1 ]]; then
			echo -n "$DELIM"
		else
			flag=0	
		fi
	fi
	
	echo -n  ${1:i:1}
done

echo 
