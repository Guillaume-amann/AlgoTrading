#!/bin/bash
export PATH=$PATH:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin

cd /Users/guillaume/AlgoTrading/

echo "------------------INIT------------------"
echo

python3 /Users/guillaume/AlgoTrading/Web/getStockPrice.py

# Run both scripts in the background and capture their outputs
output1=$(./Instruments/stockAnalysis 2>&1 & pid1=$!)
output2=$(./Instruments/optionPricer 2>&1 & pid2=$!)
output3=$(cd StatTests && dune exec ./_build/default/Test.exe 2>&1 & pid3=$!)

# Wait for both processes to finish
wait $pid1
wait $pid2
wait $pid3

# Send email with combined output
osascript -e "do shell script \"echo '$output1\n\n$output2\n\n\n$output3\n\nSee more here: https://github.com/Guillaume-amann/AlgoTrading' | mail -s 'Stock Alert' amann.guill@gmail.com\""
echo "Email sent."
echo
echo
echo "------------------END------------------"