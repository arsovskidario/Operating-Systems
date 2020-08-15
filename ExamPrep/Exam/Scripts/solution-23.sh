#!/bin/bash


if [ $# -ne 2 ];then
	echo "Invalid args"
	exit 1
fi

if [[ ! -d "$1" ]];then
	echo "not a directory"
	exit 2
fi


find $1 -type f 2>/dev/null | egrep "vmlinuz\-[0-9]+\.[0-9]+\.[0-9]+\-$2" | sort -f "-" -nrk 2 | head -n 1 

