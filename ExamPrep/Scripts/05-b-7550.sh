#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid arguments"
	exit 1
fi

PROCESSES=$(ps -u $1 -o pid,cmd)

COUNT=$( printf "$PROCESSES\n" | wc -l)
printf "Number of processes : $COUNT\n"

for((i=1;i<=$COUNT;i++))
do
      printf "$PROCESSES\n" |tr -s " " | head -n $i | tail -n 1 | egrep -o "\s[0-9]*\s" | xargs -I{} -n 1 kill -KILL {} 
done


