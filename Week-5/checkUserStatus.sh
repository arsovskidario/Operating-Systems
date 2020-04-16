#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid arguments"
	exit 2 
fi

USER_ID=$1

ERROR_STATUS=1

while : 
do

	if [ $ERROR_STATUS -eq 1 ]; then
		who | grep -w $USER_ID >/dev/null # Output not specified  
		ERROR_STATUS=$?
	else
		break 
	fi

	sleep 1
done

echo "Done" 
