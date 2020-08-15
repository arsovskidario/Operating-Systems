#!/bin/bash

if [ "$1" == "-l" ];then
	ls -lA ./ | egrep "(.*\.gz|.*\.tgz)$"
fi


if [ -f $1 ];then
	DST=./
	if [ -d $2 ];then
		DST=$2
	fi

	tar -zxvf $1 $2
fi
