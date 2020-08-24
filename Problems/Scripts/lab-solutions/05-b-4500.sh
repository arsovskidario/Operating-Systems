#!/bin/bash


if [ $# -ne 1 ];then
	echo "Invalid arguments" 
fi

USER_ID=$1

	while [ $(who | egrep -c "$USER_ID") -eq 0 ]; do
			sleep 1
	done
