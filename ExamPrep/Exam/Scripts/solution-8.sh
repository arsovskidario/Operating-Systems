#!/bin/bash

find . -type f -printf "%n %f\n" 2>/dev/null | sort -nrk 1 | head -n 5 | cut -d " " -f 2 
