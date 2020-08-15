#!/bin/bash

LIST=$(ls -lA ./ | egrep "(.*\.gz|.*\.tgz)$" | awk -F '_' '{printf "%s (%s)\n",$1,$2}'|tr -d ".gz" | tr -d ".tgz" |  tr -s " " |  cut -d " " -f 9,10) 

if [ "$1" == "-l" ];then
	printf "$LIST\n"
	exit 2 
fi

if [ "$(printf "$LIST\n" | egrep -c "${1}")" -gt 1 ];then
	MATCHES=$( printf "$LIST\n" | egrep "$1" | awk 'BEGIN{COUNT=1} {print COUNT,$1 (COUNT=COUNT+1);next}')

	printf "$MATCHES\n"
fi

if [ -f $1 ];then
	DST=./
	if [ -d $2 ];then
		DST=$2
	fi

	tar -xvf $1 -C $2
fi
