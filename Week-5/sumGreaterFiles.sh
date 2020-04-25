#!/bin/bash

        if [ $# -ne 2 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        DIR=$1
        NUMBER=$2

        find $DIR -type f -printf "%f %b \n" 2>/dev/null | awk -v NUMBER=$NUMBER 'BEGIN{SUM=0}{ if($2>NUMBER) SUM+=$2} END{printf "Result :%s \n",SUM}'
