#!/bin/bash


sed -r "s/^[0-9]*\sg\.\s-\s//" books | awk 'BEGIN{counter=1} {printf "%s. %s\n",counter,$0;(counter+=1)}' | sort -k 2 

