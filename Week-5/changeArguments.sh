#!/bin/bash

if [ $# -eq 0 ] ; then 
  exit 2
fi

#set Ana Dario Mama tato
echo $#
while [ $# -gt 0 ] ; do
	echo $1
	shift 1
done

