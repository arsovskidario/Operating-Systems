#!/bin/bash

if [ $# -ne 2 ];then
	echo "Invalid args"
	exit 1 
fi

if [[ ! -f "$1" ]] || [[ ! -f "$2" ]];then
	echo "No files specified"
	exit 2
fi


DESC=$(cat $1 | awk -F ',' '{printf "%s,%s,%s\n",$2,$3,$4}' | sort | uniq )


while read line;
do
	#echo $line
	cat $1 | egrep ",$line$" | sort -nk 1 | head -n 1  >> "$2"

done < <(echo -e "$DESC")
