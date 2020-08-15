#!/bin/bash

if [ $# -ne 3 ];then
	echo "Invalid args"
	exit 1
fi


if [[ ! -d $1 ]]; then
	echo "not dir"
	exit 2

fi

if [[ ! -d $2 ]]; then
	echo "Not dir"
	exit 3
fi


if [[ "$(whoami)" == root ]];then
#	find $1 -type f -printf "%p\n" | egrep ".*/.*$3.*"
	find $1 -type f -printf "%p\n" | egrep ".*.*$3.*" | xargs -I {} mv {} $2
fi
