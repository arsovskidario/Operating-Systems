#!/bin/bash

BRACKETS="$(grep -wo "[{}]*" sourceFile.c  | xargs -I{} echo -n {})"
MAX_COUNTER=0
COUNTER=0
for (( i=0;i<${#BRACKETS};i++ )); do
	if [[ "${BRACKETS:$i:1}" == "{" ]]; then
		((COUNTER=COUNTER+1))	
	else
	       ((COUNTER=0))
	fi
	
	if [ $COUNTER -gt $MAX_COUNTER ]; then
		((MAX_COUNTER=COUNTER))
	fi
done

echo "Max depth is ${MAX_COUNTER} "
