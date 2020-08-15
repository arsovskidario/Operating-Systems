#!/bin/bash

read -p "Enter file name : " FILE


MAX_LEVEL=0

if [ -e $FILE ]; then
	RESULT=$(cat $FILE | egrep -o "[\{\}]" | xargs echo  | tr -s " ")
	
	COUNT=0
	for(( i=0;i<${#RESULT};i++ )); do 
	
	     if [ "${RESULT:$i:1}" == "{" ]; then
		     ((COUNT=COUNT+1))
	     fi	     
		
	     if [ "${RESULT:$i:1}" == "}" ]; then
		     ((COUNT=COUNT-1))
	     fi

	     if [ ${COUNT} -gt ${MAX_LEVEL} ]; then
		     MAX_LEVEL=$COUNT
	     fi 

	done

	echo "Max level of nesting is : $MAX_LEVEL" 
	exit 0
fi

exit 1 


	
