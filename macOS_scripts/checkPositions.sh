#!/bin/bash
export PATH=$PATH:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin

cd /Users/username/path/to/your/local/clone/

cp Portfolio/Positions.csv Portfolio/copyPositions.csv

csv_file="Portfolio/Positions.csv"
max_jobs=7  # Set the maximum number of concurrent jobs | Apple M1 chip: 8 cores
current_jobs=0

SECONDS=0

{
    read # Skip the header line
    while IFS=, read -r ticker priceBought volume posReturn posLength; do
        index=$(awk -F, -v ticker="$ticker" '$1 == ticker {print NR; exit}' "$csv_file")
        #echo "Processing ticker: $ticker at line $index"

        ./Portfolio/checkPos "$ticker" "$index" &

        # Check if we've reached the maximum number of jobs
        ((current_jobs++))
        if [ "$current_jobs" -ge "$max_jobs" ]; then
            wait
            current_jobs=0
        fi

    done
} < "$csv_file"

wait
echo "Total execution time: $SECONDS seconds"
# rm Portfolio/Positions.csv
# mv Portfolio/copyPositions.csv Portfolio/Positions.csv