#!/bin/bash

if [ $# -lt 1 ] || [ $# -gt 2 ];then
	echo "Invalid args"
	exit 1
fi


if [ -z "$2" ];then
	find $1 -xtype l 2>/dev/null
else
	find $1 -type f -printf "%f %n\n" 2>/dev/null | awk -v hard=$2 '{if($2 == hard) print $1}'
fi
