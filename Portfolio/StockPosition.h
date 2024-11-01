#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include "../Instruments/Stocks.h"
using namespace std;

class Position {
private:
    string ticker;
    string dateStart;
    float priceBought;
    int volume;
    float posReturn;
    float posLength;

    const string filename = "/Users/guillaume/Downloads/Perso/Informatique/C++/AlgoTrading/Portfolio/Positions.csv";
    bool tickerExistsInFile(string tickerToCheck, string filename) {
        ifstream file(filename);

        size_t tickerLength = tickerToCheck.size();
        size_t matchIndex = 0;

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
        cout << "BUY" << ticker << "..." << endl;
    }

    // Private method for selling
    void sell() {
        cout << "SELL" << ticker << "..." << endl;
        // if (pow(posReturn, 1.0 / posLength) >= 1.1) {
        //     cout << "Selling " << ticker << "..." << endl;
        // }
    }

public:
    Position (const string &ticker): ticker(ticker), priceBought(0), volume(0), posReturn(0), posLength(0) {

        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream dateStream;
        dateStream << ltm->tm_mday << "/"
                   << 1 + ltm->tm_mon << "/" 
                   << 1900 + ltm->tm_year;
                   
        dateStart = dateStream.str();

        if (tickerExistsInFile(ticker, filename)) {
            sell();
        } else {
            buy();
        }
        saveDailyPosition();
    }

    void saveDailyPosition() const {
        ofstream outFile(filename, ios::app);
        outFile << ticker << "," << dateStart << "," << priceBought << "," << volume << "," << posReturn << "," << posLength << '\n';;
        outFile.close();
    }

    string getTicker() { return ticker; };
    string getDateStart() { return dateStart; };
    float getPriceBought() { return priceBought; };
    int getVolume() { return volume; };
    float getPosReturn() { return posReturn; };
    float getPosLength() { return posLength; };
};