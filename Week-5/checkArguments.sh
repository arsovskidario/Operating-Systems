#!/bin/bash

for i in $@
do
	if [ -f $i ];then
		echo "$i is a file, contents:"
		cat $i
	elif [ -d $i ];then
		echo "$i is a directory"
		NUMBER_CONTENTS=$(ls $i | wc -l )
		echo "Files greater than directories content : "
		find $i -type f -printf "%f %b \n" 2>/dev/null | awk -v NUMBER=$NUMBER_CONTENTS '{if($2>NUMBER) printf "%s \n",$1 }'
	fi
done	
