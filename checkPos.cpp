#include <iostream>
#include "Portfolio/StockPosition.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <ticker> <line_number>" << endl;
        return 1; // Exit with error code
    }

    string ticker = argv[1]; // The first argument is the ticker
    int line = stoi(argv[2]); // The second argument is the line number

    Position myPosition(ticker, line); // Create Position object with the arguments

    return 0;
}