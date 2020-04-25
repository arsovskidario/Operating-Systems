#!/bin/bash

if [ $# -ne 1 ] ; then
	echo "Invalid arguments" 
	exit 3
fi

USER=$1

ps -o user,pid,rss,vsz | grep -w "$USER" |tr -s " " | sort -nrk 4 | awk '{printf "PID:%s RATION:%s \n",$2,$3/$4}'

