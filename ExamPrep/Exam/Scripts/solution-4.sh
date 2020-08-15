#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Invalid arguments"
	exit 1
fi


if [[ ! -f "$1" ]]; then
	echo "First arg is not file"
	exit 2
fi

if [[ ! -f "$2" ]]; then
	echo "Second arg is not file"
	exit 3
fi


WINNER= 

if [ "$(wc -l $1 | cut -d " " -f 1)" -ge "$(wc -l $2 | cut -d " " -f 1)" ]; then
	WINNER="$1"
else
	WINNER="$2"
fi


# SONGNAME=$(cat $1 | cut -d " " -f 4-)

FILENAME="$(cat $1 | cut -d " " -f 2 | sort | uniq )"

for i in $FILENAME
do
	 touch "$i.songs"
	cat $1 | egrep "\s$i\s" | cut -d " " -f 4- > "$i.songs" 
done



