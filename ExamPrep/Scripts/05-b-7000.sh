#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Not enough params"
fi


for i in "$@"  
do
	if [ -f $i ];then
		printf "$i : $(cat $i | wc -l )\n"
	else
		echo "$i doesn't exist" 
	fi	
done
