#!/bin/bash

read -p "Enter number " NUMBER

if [ $(($NUMBER%2)) -eq 0 ]; then
	echo "Even"
else 
	echo "Not Even"
fi
