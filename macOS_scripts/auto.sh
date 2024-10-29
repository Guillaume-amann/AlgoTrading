#!/bin/bash
export PATH=$PATH:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin

cd /Users/username/path/to/your/local/clone/

echo "------------------INIT------------------"
echo
output=$(./Instruments/stockAnalysis)
osascript -e "do shell script \"echo '$output \n\n See more here: https://github.com/Guillaume-amann/AlgoTrading' | mail -s 'Stock Alert' your.address@mail.com\""
echo "Email sent."
echo
echo "------------------END------------------"