#!/bin/bash

if [ $# -ne 2 ];then
	echo "Invalid arguments"
	exit 2
fi

RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"

if [ "$1" == "-r" ] ; then
	echo -e "$RED$2"
elif [ "$1" == "-g" ]; then
	echo -e "$GREEN$2"
elif [ "$1" == "-b" ]; then
	echo -e "$BLUE$2"
fi
echo -e '\033[0m'
