#!/bin/bash

echo "------------------INIT------------------"
echo
(./Instruments/stockAnalysis; echo "See more here: https://github.com/Guillaume-amann/AlgoTrading") | mail -s "Stock Alert" amann.guill@gmail.com amann.antoine@gmail.com
echo "Email sent."
echo
echo "------------------END------------------"