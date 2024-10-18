#!/bin/bash

echo "------INIT------"

DURATION=40
INTERVAL=10
#all in seconds

START=$(date +%s)

while [ $(($(date +%s) - START)) -lt $DURATION ]; do
	TEMP=$(vcgencmd measure_temp)
	echo "Current temperature: $TEMP"

	./bondprice
	echo -e "\nDone."

	TEMP=$(vcgencmd measure_temp)
	echo "Temperature after execute: $TEMP"

	sleep $INTERVAL
done

echo "------END------"
