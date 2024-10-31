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
    "Position")
        csv_file="Portfolio/Positions.csv"

        # Loop through each line in the CSV file
        while IFS=',' read -r first_item _; do
            ./PortfolioManager "$first_item"
        done < "$csv_file"
        ;;
    *)
        echo "Invalid option. Please choose Stock, Bond, or Option."
        ;;
esac
echo
echo "------------------END------------------"