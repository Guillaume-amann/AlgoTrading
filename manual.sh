#!/bin/bash
cd /Users/guillaume/Downloads/Perso/Informatique/C++/AlgoTrading/

echo "------------------INIT------------------"
echo
echo "What mission? (Stock/Bond/Option)"
read mission
echo

case "$mission" in
    "Bond")
        ./Instruments/bondPricer
        ;;
    "Option")
        ./Instruments/optionPricer
        ;;
    "Stock")
        ./Instruments/stockAnalysis
        ;;
    *)
        echo "Invalid option. Please choose Stock, Bond, or Option."
        ;;
esac
echo
echo "------------------END------------------"