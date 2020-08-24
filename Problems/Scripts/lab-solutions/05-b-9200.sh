#!/bin/bash


touch deletion.log

FLAG=0

if [ "$1" == "-r" ];then
	FLAG=1
fi

for i in "$@"
do
	if [ ${FLAG} -eq 1 ]; then
		printf "$(date +"%F %r") $i" > deletion.log
		rm -rf $i
	else
		if [ -d ${i} ];then
			if [ -z "$(ls -A ./${i})" ]; then 
				echo "IN $i"
				printf "$(date +"%F %r") $i" > deletion.log
				rm -rf ./$i
			fi
		elif [ -f ${i} ]; then
			printf "$(date +"%F %r") $i" > deletion.log
			rm -rf $i

		fi
		
	fi	
done	
