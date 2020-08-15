#!/bin/bash

if [ $# -ne 2 ];then
	echo "Invalid args "
	exit 1
fi


if [[ ! -d "./a" ]]; then
	mkdir "a"
fi

if [[ ! -d "./b" ]];then
	mkdir "b"
fi

if [[ ! -d "./c" ]];then
	mkdir "c"
fi


if [[ "$1" =~ ^[0-9]*$ ]] && [[ "$2" =~ ^[0-9]*$ ]];then

	FILES=$(find . -type f 2>/dev/null)

	for i in $FILES
	do
		LINES=$(wc -l $i | cut -d " " -f 1)
		if [ $LINES -lt $1 ];then
			mv $i ./a
		elif [ $LINES -lt $2 ];then
			mv $i ./b
		else
			mv $i ./c	
		fi
	done


else 
	echo "Params are not numbers"
	exit 2
fi


