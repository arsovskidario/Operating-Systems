#!/bin/bash

read -p "Enter files : " file1 file2 file3

if [[ -e $file1 && -e $file2 ]]; then
	cat $file1 $file2 | sort > $file3
	exit 0
fi 

exit 1
