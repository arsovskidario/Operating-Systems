#!/bin/bash

[ $# -gt 0 ] || echo "No parametar" 

if [[ $1 =~ ^[a-zA-Z0-9]*$ ]]; then
   echo "Is valid" 
else
   echo "Invalid" 
fi

