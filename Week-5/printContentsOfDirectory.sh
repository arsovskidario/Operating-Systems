#!/bin/bash

SRC_DIR=$1
ARG=$2
find $SRC_DIR -type f -printf "%f %s \n" |sort|grep -wv ".*.sh"| xargs -I{} -n 1 echo "{} Bytes"
if [ "$ARG" != "-a" ]; then	
find $SRC_DIR -type d |sort| grep -wv "\./\..*"| xargs  -d $'\n' sh -c  'for arg do printf "$arg $(ls $arg | wc -l ) contents\n";done'       
else 
	find $SRC_DIR -type d |sort| xargs  -d $'\n' sh -c  'for arg do printf "$arg $(ls -a $arg | wc -l ) contents\n";done'
fi



