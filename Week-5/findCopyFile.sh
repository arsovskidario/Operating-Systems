#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments"
	exit 2
fi

#Check if it is a dir or a file 
FILE_NAME=$1
DIR_NAME=$2

DIR_CONTENT=$(find ${DIR_NAME} -type f -printf "%f " 2>/dev/null)

for i in ${DIR_CONTENT} 
do
	cmp ${FILE_NAME} $i
	if [ $? -eq 0 ]; then
		echo $i
	fi
done
