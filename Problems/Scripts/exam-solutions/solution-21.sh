#!/bin/bash

if [[ ! "$(whoami)" == "root" ]];then
	echo "Not root"
	exit 1
fi

USERS=$(users)

while read line;
do
	RSS_SIZE=$(ps -u $line -o user,pid,%cpu,%mem,vsz,rss,tty,time,cmd | awk 'BEGIN{COUNT=0} {COUNT+=$6} END{print COUNT}')
	echo "$line $RSS_SIZE"
	NUMBER_PROCESSES=$(ps -u $line -o user,pid,%cpu,%mem,vsz,rss,tty,time,cmd | wc -l)
	((AVGSIZE=$RSS_SIZE/$NUMBER_PROCESSES))

        PID=$(ps -u $line -o pid,rss| sort -nrk 2 | head -n 1 | tr -s " " | cut -d " " -f 3
)
	
	# Kill -KILL "$PID"

done < <(echo -e "$USERS")
