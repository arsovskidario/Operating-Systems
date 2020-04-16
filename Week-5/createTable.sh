#!/bin/bash

echo "<table>" 
echo "<tr> "
echo "	<th>Username</th> " 
echo "	<th>group</th> "
echo "	<th>login</th> "
echo "	<th>GECKO</th> "
echo "</tr> "

for ((i=1;i<=$(wc -l passwd.txt | cut -d " " -f 1);i++)); do
	USERNAME=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":" -f 1)
	GROUP=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":" -f 4)
	SHELL=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":" -f 7)
	GECKO=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":" -f 5)
	echo "<tr>"
	echo "<td>${USERNAME}</td>"
	echo "<td>${GROUP}</td>"
	echo "<td>${SHELL}</td>"
	echo "<td>${GECKO}</td>"
	echo "</tr>"

done

echo "</table>"
