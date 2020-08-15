#!/bin/bash

if [ $# -ne 1 ];then
	echo "Inavlid arguments"
	exit 1
fi

if [[ ! -d $1 ]];then
	echo "Not file"
	exit 2
fi


RESULT=$(find $1 -printf "%p %T@\n" 2>/dev/null | egrep ".tgz" | egrep "[a-zA-Z0-9]+_report\-[0-9\.]+\.tgz" | sort -nrk 2 | head -n 1 | cut -d " " -f 1 )


echo "$RESULT"

if [ -n "$(tar -tvf $RESULT 'meow.txt')" ];then
	mkdir extracted
	tar -zxvf $RESULT meow.txt
	NAME=$(echo "$RESULT" | egrep "[a-zA-Z0-9]+_" | sed 's/_//')
	TIMESTAMP=$(echo "$RESULT" | egrep "report\-.*" | sed -E 's/report\-//' | sed -E 's/\.tgz//')
	mv meow.txt $NAME_$TIMESTAMP.txt
	mv $NAME_$TIMESTAMP.txt ./extracted
fi



