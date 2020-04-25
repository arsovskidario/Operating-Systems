#!/bin/bash

NEW_PATH=$(echo $PATH | tr ":" " ")
COUNT=0
for i in $NEW_PATH; do
	(( COUNT=COUNT+$(find $i -type f -executable 2>/dev/null | wc -l) )) 	
done
echo "Final result : $COUNT"
