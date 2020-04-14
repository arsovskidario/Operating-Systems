#!/bin/bash

read -p "Enter full filename :" FILENAME


echo "${FILENAME}"
echo "Number of files : $(find "${FILENAME}" -maxdepth 1 2>/dev/null | wc -l)"

