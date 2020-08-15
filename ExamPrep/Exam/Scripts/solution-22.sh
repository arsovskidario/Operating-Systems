#!/bin/bash

if [ $# -lt 1 ];then
	echo "Invalid args"
	exit 1
fi


if [[ ! -d "$1" ]];then
	echo "Not a directory"
	exit 2
fi

FLAG=0 # used for showing where to print the output
if [ $# -eq 2 ];then
	if [ -f "$2" ];then
		FLAG=1
	else
		echo "Not file"
		exit 3
	fi

fi



EXISTING=$(find . -type l -not -xtype l 2>/dev/null | xargs -I {} stat {} | egrep "File:.*" | sed 's/File://' | tr -d '[[:blank:]]')

BROKEN_COUNT=$(find . -xtype l 2>/dev/null | wc -l)

if [ "$FLAG" -eq 1 ];then
	# File exists and will inter data into it 

	while read line; do
		echo $line >> "$2"
	done < <(echo -e "$EXISTING")

	if [ -z "$BROKEN_COUNT" ];then
		BROKEN_COUNT=0
	fi

	echo -e "Broken links : $BROKEN_COUNT" >> "$2"
else
	while read line; do
                echo $line 
        done < <(echo -e "$EXISTING")

        if [ -z "$BROKEN_COUNT" ];then
                BROKEN_COUNT=0
        fi

        echo -e "Broken links : $BROKEN_COUNT" 


fi


