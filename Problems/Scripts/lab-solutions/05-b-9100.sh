#!/bin/bash

if  [ $# -ne 2 ]; then
	echo "Invalid arguments" 
	exit 1
fi

if [[ ! -d $1 ]];then 
	echo "Source is not a directory!"
	exit 2
fi

if [[ ! -d $2 ]]; then
	echo "Destination is not a directory!"
	exit 3
fi


FILES=$(find $1 -type f -printf "%f\n" 2>/dev/null)


EXTENSIONS=$(printf "$FILES\n" | egrep -o "\..*"|tr -d "." |  sort | uniq )

cd $2
printf "$EXTENSIONS\n" | xargs -I{} mkdir {} 

cd -

for i in $EXTENSIONS
do
	find $1 -type f -name "*.${i}" 2>/dev/null | xargs -I{} mv {} $2/$i 
done

