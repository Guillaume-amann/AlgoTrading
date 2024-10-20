#include <iostream>
#include <vector>
#include <string>
using namespace std;

string hist_vol(const vector<double>& dataVector, const string& flag) {
    string result;

    if (dataVector.size() == 252) {
        result += "Vector size is correct (252).\n";
        for (double value : dataVector) {
            result += to_string(value) + " ";
        }
        result += "\n";
    } else {
        cerr << "Error: Invalid vector size. Expected size is 252, but got " << dataVector.size() << ".\n";
    }

    if (flag == "y") {
        result += "Flag is valid.\n";
    } else {
        cerr << "Error: Invalid string argument. Expected 'y'.\n";
    }

    return result;
}