#!/bin/bash

if [ $# -ne 1 ]; then
	echo "No args"
	exit 1
fi


if [ -d "$1" ];then

	links=$(find "$1" -type l -printf "%p\n" 2>/dev/null)

	while read line; do

		if [[ ! -L "$line" ]];then
			if [[ ! -e "$line" ]];then
				echo "$line"
			fi
		fi	

	done < <(echo -e "$links")
fi
