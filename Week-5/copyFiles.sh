#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Invalid arguments"
	exit 1 
fi

SOURCE=$1
DESTINATION=$2
if [ -z "$DESTINATION" ]; then
	DESTINATION="./"
fi

	find $SOURCE -type f -printf -mmin -45 "%p" 2>/dev/null | xargs -I{} -n 1 cp {} DESTINATION

echo "DONE"
