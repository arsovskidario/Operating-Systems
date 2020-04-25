#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Nothing to terminate"
	exit 2
fi

USER=$1
PROCESSES=$(ps -o user,pid,cmd | tr -s " " | grep -w "$USER" | cut -d " " -f 2 )
COUNTER=0
for i in $PROCESSES
do
	echo $i
	kill -9 $i # Rest in peace process  
	(( COUNTER=COUNTER+1))
done
