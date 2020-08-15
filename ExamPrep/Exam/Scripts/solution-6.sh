#!/bin/bash

# A)

echo "Results a)"
find . -type f -printf "%p\n" 2>/dev/null | xargs -I{} -n 1 wc -l {} | awk '{if ($1 ==0) print $2}'

# B)

echo "Results b)" 
find ~ -type f -user "$(whoami)" -printf "%s %f\n" 2>/dev/null | sort -nrk 1 | head -n 5 | cut -d " " -f 2
