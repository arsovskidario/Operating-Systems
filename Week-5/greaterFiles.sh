#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments"
	exit 2
fi

DIR=$1
NUMBER=$2

find $DIR -type f -printf "%f %b \n" 2>/dev/null | awk -v NUMBER=$NUMBER '{ if($2>NUMBER) printf "%s \n",$1}' 
