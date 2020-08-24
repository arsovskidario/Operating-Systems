#!/bin/bash


for i in "$@" 
do
	if [ -f $i ];then
		if [ -r $i ]; then
			printf "$i is a file and can be read\n"
		else 
			print "$i is a file but can't be read\n"
		fi
	elif [ -d $i ];then
		printf "$i is a directory and contains these files: \n"
		COUNT_CONTENT=$(find  $i -type f 2>/dev/null | wc -l)
		find $i -type f -size -${COUNT_CONTENT}c -printf "%f\n" 2>/dev/null
	fi
done
