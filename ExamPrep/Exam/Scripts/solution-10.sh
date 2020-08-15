#!/bin/bash


cat passwd.txt | egrep ":/home/SI" | cut -d ":" -f 5,6 | sed "s/,.*:/:/" 
