#!/bin/bash

#find ~ -type f -user pesho -printf "%i %T@\n" 2>/dev/null | sort -nrk 2 | head -n 1 | cut -d " " -f 1


# Hard links = can have different names  

find ~ -type f -user pesho -printf "%n %i %f %T@\n" 2>/dev/null | awk '{if ($1 >=2) print $2,$4}' | sort -nrk 3 | head -n 1 | cut -d " " -f 1 
