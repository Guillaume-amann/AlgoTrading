#!/bin/bash

echo "------INIT------"

DURATION=40
INTERVAL=10
#all in seconds

START=$(date +%s)

while [ $(($(date +%s) - START)) -lt $DURATION ]; do

	./Pricer
	echo -e "\nDone."

	sleep $INTERVAL
done

echo "------END------"