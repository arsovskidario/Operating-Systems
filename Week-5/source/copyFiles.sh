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

	find $SOURCE -type f -mmin -45 -printf "%p" -exec cp {} $DESTINATION \; >/dev/null



echo "DONE"
