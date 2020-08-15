#!/bin/bash

read -p "Enter file directory" DIR_PATH

find $DIR_PATH -maxdepth 1 -type d 2>/dev/null | wc -l | xargs -I{} echo "Number of directories : {}"

find $DIR_PATH -maxdepth 1 -type f 2>/dev/null | wc -l | xargs -I{} echo "Number of files :{}" 
