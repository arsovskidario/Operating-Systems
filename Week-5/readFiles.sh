#!/bin/bash

read -p "Enter 3 files : " file1 file2 file3
cat file1 >> file2  
sort file2 > file3 

echo "Result after modifying files: "
cat file3
