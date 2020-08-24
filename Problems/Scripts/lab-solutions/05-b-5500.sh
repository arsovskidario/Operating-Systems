#!/bin/bash


NUM_LINES=$(cat /etc/passwd | wc -l)
CONTENT=$(cat /etc/passwd)
echo "<table>"
for(( i=1;i<=$NUM_LINES;i++ )); do
	LINE=$(echo "$CONTENT" | head -n $i | tail -n 1)
	USERNAME=$(echo "$LINE" |cut -d ":" -f 1)
	GROUP=$(echo "$LINE" |cut -d ":" -f 4)
	USHELL=$(echo "$LINE" |cut -d ":" -f 7)
	GECKO=$(echo "$LINE" |cut -d ":" -f 5)

	echo "<tr>"
	echo "	<th>$USERNAME</th>"
	echo "	<th>$GROUP</th>"
	echo "	<th>$USHELL</th>"
	echo "	<th>$GECKO</th>"
	echo "</tr>"

done

echo "</table>"
