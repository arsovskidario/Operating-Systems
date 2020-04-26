#!/bin/bash

if [ $# -eq 0 ];then
	echo " So you don't want to delete anything ?"
	exit 2
fi

RECURSIVE=0 # 0=false 1=true
SRC_BACK=/home/dario/Development/Operating-Systems/Week-5/DeleteWithBackup/backup
if [ "$1" == "-r" ]; then
	((RECURSIVE=1))
fi

for i in $@ 
do
	if [ "$i" == "-r" ]; then
		continue
	fi
	
	NEW_NAME=""$i"_$(date +"%y-%m-%d_%H:%M:%S" | tr ":" "-"
).tar"
	if [  $(ls $i | wc -l ) -eq 0 ]; then
		tar -cvf $NEW_NAME $i 
		mv $NEW_NAME $SRC_BACK	
		rmdir $i
	elif [ $RECURSIVE -eq 1 ]; then
		echo "$NEW_NAME"
		tar -cvf $NEW_NAME  --exclude=./$NEW_NAME $i
                mv $NEW_NAME $SRC_BACK
                rm -r $i	
	fi
done

