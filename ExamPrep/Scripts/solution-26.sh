#!/bin/bash

if [ $# -ne 2 ];then
	echo "invalid args"
	exit 1
fi


if [[ ! -d $1 ]]; then
	echo "not a directory"
	exit 2
fi


NUMBER=0

USERS=$(cat $2 |cut -d ":" -f1 | egrep -o "[a-zA-Z\-]+\s[a-zA-Z\-]+\s" | sed 's/\s$//' | sort | uniq)


touch dict.txt

while read line;
do
	echo "$line;$NUMBER" >> dict.txt
	RESULT=$(cat $2 | egrep "$line" | cut -d ":" -f 2)
	echo "$RESULT" > $NUMBER.txt
	((NUMBER+=1))

done < <(echo -e "$USERS")


