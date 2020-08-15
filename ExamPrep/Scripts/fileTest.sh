#!/bin/bash

if [ -e foo.txt ] && [ -e bar.txt ]; then
	echo "Both exist"
	if [ foo.txt -nt bar.txt ]; then
		echo " Foo is newer" 
	else
		echo " Foo is older" 
	fi
	exit 0
fi

exit 1

