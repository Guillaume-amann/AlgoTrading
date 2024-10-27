#include <iostream>
#include <fstream>
#include <cmath>
#include "Instruments/Stocks.h"
using namespace std;

class Position {
private:
    string ticker;
    string dateStart;
    float priceBought;
    int volume;
    float posReturn;
    float posLength;

    const string filename = "Positions.csv";

    bool tickerExistsInFile(string tickerToCheck, string filename) {
        ifstream file(filename);

        size_t tickerLength = tickerToCheck.size();
        size_t matchIndex = 0;

        if (!file.is_open()) {
            cerr << "Error: Could not open the file " << filename << std::endl;
            return false;
        }

        char ch;
        while (file.get(ch)) {
            if (ch == tickerToCheck[matchIndex]) {
                matchIndex++;
                //Check if the entire ticker has been matched
                if (matchIndex == tickerLength) {
                    char nextChar = file.peek();
                    if (nextChar == ',' || nextChar == '\n' || nextChar == EOF) {
                        file.close();
                        return true;
                    } else {
                        matchIndex = 0; //Reset match index if followed by other characters
                    }
                }
            } else {
                matchIndex = (ch == tickerToCheck[0]) ? 1 : 0;
            }
        }

        file.close();
        return false;
    }

    // Private method for buying
    void buy() {
        if (rsi >= 1.1 && Dmacd) {
            cout << "Selling " << ticker << "..." << endl;
        }
        cout << "Buying " << ticker << "..." << endl;
        // Add specific logic for buying a position here
    }

    // Private method for selling
    void sell() {
        if (pow(posReturn, 1.0 / posLength) >= 1.1) {
            cout << "Selling " << ticker << "..." << endl;
        }
    }

public:
    Positionconst (Asset &asset): ticker(asset.ticker), priceBought(0), volume(0), posReturn(0), posLength(0) {
        if (tickerExistsInFile(ticker, filename)) {
            sell();
            saveDailyPosition();
        } else {
            buy();
            saveDailyPosition();
        }
    }

    void saveDailyPosition() const {
        ofstream outFile(filename, app);
        outFile << ticker << "," 
            << dateStart << "," 
            << priceBought << "," 
            << volume << "," 
            << posReturn << "," 
            << posLength << endl;
        file.close();
    }
};