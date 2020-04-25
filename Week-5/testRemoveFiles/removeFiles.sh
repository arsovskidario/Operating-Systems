#!/bin/bash

RECURSIVE=0
if [ "$1" == -r ]; then
	((RECURSIVE=1))
fi

for i in $@ 
do
	if [ "$i" == "-r" ]; then
	     continue
	fi
	
	NUM_FILES=$(ls $i | wc -l)
	
	if [ $NUM_FILES -eq 0 ]; then
		rmdir $i
	    	echo "[$(date +"%y-%m-%d %T")] $i" >> ~/Development/Operating-Systems/Week-5/logs/remove.log 
	fi

	if [ $RECURSIVE -eq 1 ]; then
		rm -r $i
		echo "[$(date +"%y-%m-%d %T")] $i" >> ~/Development/Operating-Systems/Week-5/logs/remove.log
 	fi 	

done	
