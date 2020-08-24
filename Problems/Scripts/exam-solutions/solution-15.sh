#!/bin/bash


if [ "$(whoami)" == "root" ]; then
	USERS=$(cat passwd.txt )
	while read line; do 
		U_BASH=$(echo "$line" | cut -d ":" -f 6)
		if [[ ! "$U_BASH" =~ ^/home/ ]];then
			if [[ ! -r "$(echo "$U_BASH" | egrep -o "/home/")" ]];then
			echo "$line"
			fi
		fi


	done < <(echo -e "$USERS")
else
	echo "Not root"
	exit 1
fi
