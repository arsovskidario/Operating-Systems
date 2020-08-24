#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid arguments"
	exit 2
fi

ps -u $1 -o pid,cmd,rss,vsz | tail -n +2 | awk '{print $NF,$0}' | sort -rnk 1 | cut -d " " -f 2- | awk '{print $2,($NF/$(NF-1))}' 
