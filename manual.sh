#!/bin/bash

echo "------INIT------"
echo
echo "What mission? (Stock/Bond/Option)"
read mission
echo

case "$mission" in
    "Bond")
        ./Pricer
        ;;
    "Option")
        ./Opt
        ;;
    "Stock")
        echo "AAPL" | ./AAPL
        ;;
    *)
        echo "Invalid option. Please choose Stock, Bond, or Option."
        ;;
esac
echo
echo "------END------"