#!/bin/bash

if [[ $# -lt 1 ||  $# -gt 2 ]]; then
	echo "Invalid argumnets"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "First argument isn't a directory"
	exit 2
fi

SRC=$1
DEST=

if [ -z "$2" ];then
	DEST=$(find . -maxdepth 1 -type d -printf "%p %A@\n" 2>/dev/null | sort -nk 2 | tail -n 1 | cut -d " " -f 1 )
else
	DEST=$2
fi

if [[ ! -d $DEST ]]; then
	echo "Second arguments isn't a directory" 
	exit 3
fi

find $SRC -type f -mmin -45 -printf "%p\n" 2>/dev/null | xargs -I{} cp {} $DEST




