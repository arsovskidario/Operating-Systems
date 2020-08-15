#!/bin/bash

BEGIN1=1551168000
END1=1551176100

STUDENTS=$(cat passwd.txt | egrep "/home/SI/" | sed 's/^s//')


while read line;do
	BASH=$(echo "$line" |cut -d ":" -f 6 | egrep "^/home/*")

	if [ -n "$BASH" ];then
	
		FN1=$(echo $line | cut -d ":" -f 1)
		NAME1=$(echo $line | cut -d ":" -f 5 | egrep -o "[a-zA-Z]+\s[a-zA-Z]+")
		
		printf "$FN1 $NAME1\n"

		# find "$BASH" -maxdepth 0 -printf "%C@\n" 2>/dev/null | awk -v BEGIN=$BEGIN1 -v END=$ENDi1 -v FN=$FNi1 -v NAME=$NAMEi1 '{if($1> BEGIN && $1<END) printf "%s %s\n",FN,NAME else printf "%s %s\n",FN,NAME}'
	fi

done < <(echo -n "$STUDENTS")


#find /home/SI -maxdepth 1 -type d -newerct '@1551168000' -not \
#-newerct '@1551176100' -exec grep -F :{}:/etc/passwd \; \
#| cut -d ':' -f 1,5 | cut -c 2- | cut -d ',' -f 1 | tr ':' '\t'
