#!/bin/bash

cat passwd.txt | egrep "/home/Inf" |  egrep  ":[a-zA-Z]*\s[a-zA-Z]*a[,:]" | cut -c 3,4 | sort | uniq -c  | sort -rnk 1 | head -n 1
