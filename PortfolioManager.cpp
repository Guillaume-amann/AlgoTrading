#include <iostream>
#include "Portfolio/StockPosition.h"
using namespace std;

int main() {
    string ticker;
    cin >> ticker;
    Position myPosition(ticker);
    
    return 0;
}