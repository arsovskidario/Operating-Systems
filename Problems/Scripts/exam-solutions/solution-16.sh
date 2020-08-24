#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Invalid args"
	exit 1
fi

if [ -f "$1" ];then

	FIRST_SET=$(cat $1 | egrep "^$2=" | cut -d "=" -f 2)
	SECOND_SET=$(cat $1 | egrep "^$3=" | cut -d "=" -f 2)

	while read line;
	do
		for i in $line
		do
			SECOND_SET=$(echo $SECOND_SET | sed -E "s/\s?$i\s?//")
		done

	done < <(echo -e "$FIRST_SET")

	RESULT=$(cat $1 | sed -E "s/^$3=.*/$3=$SECOND_SET/")

	echo "$RESULT" > $1

else
	echo "Not a file"
	exit 2
fi
