#!/bin/bash

if [ $# -ne 1 ] ;then
	echo "Invalid args"
	exit 1
fi


if [[ ! "$1" =~ ^[0-9]+$ ]];then
	echo "not a number"
	exit 2
fi


if [ "$(whoami)" == "root" ]; then
	
	USERS=$(users)

	while read line;do
		echo $line
		SIZE=$(ps -u "$line" -o pid,%cpu,%mem,vsz,rss,cmd | tr -s " " | awk 'BEIGN{COUNT=0} {(COUNT+=$5)} END{print COUNT}')

		if [ "$SIZE" -gt "$1" ]; then
			pid="$(ps -u "$line" -o pid,rss |tr -s " " | sort -nrk 2 | head -n 1 | cut -d  " " -f 2)"
			echo "$pid"
			# Kill -KILL "$pid" 
			
		fi

	done < <(echo -e "$USERS")
fi
