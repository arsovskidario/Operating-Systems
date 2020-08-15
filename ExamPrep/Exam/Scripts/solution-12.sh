#!/bin/bash


INODE=$(find ~ -type f -user "velin" -printf "%i %T@\n" | sort -nrk 2 | head -n 1 | cut -d " " -f 1)


find ~ -type f -user "velin" -inum "$INODE" -printf "%f %d\n" 2>/dev/null | sort -nk 2 | head -n 1 | cut -d " " -f 1 
