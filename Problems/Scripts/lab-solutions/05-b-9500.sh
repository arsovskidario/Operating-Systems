#!/bin/bash

if [ $# -ne 2 ];then
	echo "Invalid argumennts"
	exit 1
fi

if [ "$1" == "-r" ]; then
	echo -e "\033[0;31m $2"
elif [ "$1" == "-g" ]; then
	echo -e "\033[0;32m $2"
elif [ "$1" == "-b" ]; then
	echo -e "\033[0:34m $2"
fi

echo -e "\033[0m"
