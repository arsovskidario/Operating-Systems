#!/bin/bash

if [ $# -ne 1 ];then
	echo "Invalid arg" 
	exit 1
fi

if [ "$(whoami)" == "root" ];then
	PSARG=$(ps -u "$1" -o user,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | tail -n +2 |  wc -l)
	USERS=$(users)
	TIME_CONSUMED=0
	for i in $USERS
	do
		UCOUNT=$(ps -u "$i" -o user,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | tail -n +2 | wc -l ) 
		
		if [ $UCOUNT -gt $PSARG ]; then
			echo "$i"
		fi

		UTIME=$(ps -u "$i" -o user,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | tail -n +2 | awk 'BEGIN{COUNT=0}{(COUNT+=$9)} END{print COUNT}' )	
		((TIME_CONSUMED+=$UTIME))	
	done

	echo $TIME_CONSUMED

	KILLS=$(ps -u "$1" -o user,pid,%cpu,%mem,vsz,rss,tty,stat,time,command | tail -n +2 | awk -v AVG=$TIME_CONSUMED '{if ($9 > AVG) print $2}')

	#for i in $KILLS
	#do
	#	kill -KILL $i 
	#done

else
	echo "Not root"
	exit 2
fi
