#!/bin/bash

echo "------INIT------"

DURATION=40
INTERVAL=10
#all in seconds

START=$(date +%s)

while [ $(($(date +%s) - START)) -lt $DURATION ]; do

	echo "AAPL" | ./AAPL
	echo -e "\nDone."

	rm -rf AAPL.dSYM

	sleep $INTERVAL
done

echo "------END------"