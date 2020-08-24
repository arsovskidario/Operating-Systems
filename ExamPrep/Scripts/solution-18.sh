#!/bin/bash

find /home/ -type f -printf "%u %f %T@\n" 2>/dev/null | sort -nrk 3 | head -n 1 | cut -d " " -f 1,2

