#!/bin/bash

FLAG=0

if [ "$1" == "-r" ];then
	FLAG=1
fi

for i in "$@" 
do
	DATE=$(date +"%F-%r" | tr ":" "-" | tr -d " ")

     if [ $FLAG -eq 0 ]; then

	if [ -f $i ]; then
		tar -zcvf ""$i"_$DATE.gz" ${i}
		rm $i
	elif [ -d $i ]; then
		
		if [ -z "$(ls -A $i)" ];then
			tar -cvf ""$i"_$DATE.tgz" ${i}
			rm -r $i
		fi
	fi

     else
	if [ -f $i ]; then
                tar -zcvf ""$i"_$DATE.gz" $i
                rm $i
        elif [ -d $i ];then
		tar -cvf ""$i"_$DATE.tgz" $i
		rm -rf $i
	fi

     fi	
done
