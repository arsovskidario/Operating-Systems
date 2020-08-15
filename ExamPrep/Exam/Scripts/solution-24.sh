#!/bin/bash

if [[  "$(whoami)" != "root" ]];then
	echo "Not root"
	exit 1
fi

USERS=$(cat /etc/passwd | cut -d ":" -f 1)

while read line; 
do
	if [ "$line" != "root" ];then
		HOME=$(cat /etc/passwd | egrep "$line" | cut -d ":" -f 6 | egrep "/home/")

		ROOT_MEM=$(ps -u root -o rss | awk 'BEGIN{count=0} {count+=$1} END{print count}')

		if [ -z "$HOME" ] || [ "$(stat $HOME -c %U)" != "$line" ] || [ -n "$(find $HOME -maxdepth 0 -user $line ! -writable)" ];then
			USER_MEM=$(ps -u $line -o rss | awk 'BEGIN{count=0} {count+=$1} END{print count}')

			if [ "$USER_MEM" -gt "$ROOT_MEM" ];then
				if [ "$line" != "dario" ];then
					killall -u "$line"
				fi
			fi

		fi


	fi
done < <(echo -e "$USERS")
