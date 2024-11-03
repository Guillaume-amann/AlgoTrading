#!/bin/bash
export PATH=$PATH:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin

cd /Users/username/path/to/your/local/clone/

echo "------------------INIT------------------"
echo

# Run both scripts in the background and capture their outputs
output1=$(./Instruments/stockAnalysis 2>&1 & pid1=$!)
output2=$(./Instruments/optionPricer 2>&1 & pid2=$!)

# Wait for both processes to finish
wait $pid1
wait $pid2

# Send email with combined output
osascript -e "do shell script \"echo '$output1\n\n$output2\n\nSee more here: https://github.com/Guillaume-amann/AlgoTrading' | mail -s 'Stock Alert' your.address@mail.com\""
echo "Email sent."
echo
echo
echo "------------------END------------------"