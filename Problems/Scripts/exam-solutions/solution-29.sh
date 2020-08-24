#!/bin/bash

LINECOUNT=10
FLAG=0

if [ "$1" == "-n" ];then
	if [[ "$2" =~ ^[0-9]*$ ]];then
		LINECOUNT=$2
		FLAG=1
		#printf "%s %s\n" $1 $2

	else
		echo "Second parametar is not a number"
		exit 1
	fi
fi

	  while read line;
          do
		if [ $FLAG -eq 1 ]; then
			if [ "$line" == "$1" ] && [ "$line" == "$2" ];then
				continue;
			fi
		fi
		
		ID=$( printf "%s" $line |egrep "\.log" | sed -E 's/\.log//' )
		OUTPUT=$(printf "%s" $line | egrep ".log")

		TEXT=$(cat "${OUTPUT}" 2>/dev/null | tail -n $LINECOUNT)
		RESULT=$(mktemp)
		while read line; do
			TIME=$(echo "$line" | cut -d " " -f 1,2 )
			DATA=$(echo "$line" | cut -d " " -f 3- )

			printf "%s %s %s\n" $TIME $ID $DATA
		done < <(echo -e "$TEXT")


          done < <(printf "%s\n" "$@")
	
	
