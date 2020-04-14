#!/bin/bash 

for i in 1 2 3; do
	echo "In"
	echo "For"
done

for var in FOO BAR ZAS; do
	echo ${var}
done

for i in "$@"; do
	echo $i

done

