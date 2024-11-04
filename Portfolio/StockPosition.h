#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include "../Instruments/Stocks.h"
using namespace std;

class Position {
private:
    string ticker;     //ticker of the Cie
    string dateStart;  //Date of first stock purchase
    float priceBought; //Average price per stock bought
    int volume;      //Amount of stocks held
    float posReturn; //Position absolute return as a pctg of price bought premium
    float posLength; //Position duration as a fraction of a 252-day year

    const string filename = "/Users/guillaume/Downloads/Perso/Informatique/C++/AlgoTrading/Portfolio/Positions.csv";

    Stock myStock;     // Stock object to check position

public:
    Position (const string &ticker, int lineNumber): ticker(ticker), myStock(ticker) {
        ifstream file(filename);
        string line;
        
        // Skip lines until reaching the specified line number
        for (int currentLine = 0; currentLine < lineNumber; ++currentLine) {
            if (!getline(file, line)) {
                cerr << "Error: line number " << lineNumber << " exceeds file length." << endl;
                return;
            }
        }

        // Now we are at the specified line, parse it
        if (getline(file, line)) {
            istringstream ss(line);
            string field;

            getline(ss, this->ticker, ',');  // Re-assign to confirm ticker
            getline(ss, dateStart, ',');
            getline(ss, field, ',');
            priceBought = stof(field);
            getline(ss, field, ',');
            volume = stoi(field);
            getline(ss, field, ',');
            posReturn = stof(field);
            getline(ss, field, ',');
            posLength = stof(field);
        }
        file.close();
    }

    int checkPosition() {
        double posLength = (stod(myStock.getLastDate()) - stod(dateStart)) / 252;  // Converting dates to numbers (assuming yyyyMMdd format)
        double posReturn = pow((1+((myStock.getLastPrice() - priceBought)/priceBought)) , (1/posLength));
        if (posReturn > 1.1) {
            cout << "SELL " << ticker << " | @ " << (posReturn-1)*100 << " annual return"<< endl;
            return -1;  // SELL
        }
        else if (posReturn < 0.0) {
            cout << "BUY " << ticker << endl;
            return 1;   // BUY
        }
        else {
            return 0;   // HOLD
        }
    }

    string getTicker() { return ticker; };
    string getDateStart() { return dateStart; };
    float getPriceBought() { return priceBought; };
    int getVolume() { return volume; };
    float getPosReturn() { return posReturn; };
    float getPosLength() { return posLength; };
};
