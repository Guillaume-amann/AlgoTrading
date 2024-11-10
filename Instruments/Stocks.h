#include <iostream>
#include <Python.h>
#include <filesystem> 
using namespace std;

class Stock {
private:
    string ticker;
    vector<double> prices;
    vector<string> dates;
    double lastPrice;
    string lastDate;

    double RSI14;
    vector<double> MACD;

    double calculateRSI(int period = 14) {
        double gains = 0.0;
        double losses = 0.0;
        for (int i = prices.size() - period; i < prices.size() - 1; ++i) {
            double change = prices[i + 1] - prices[i];
            if (change > 0) {
                gains += change;
            } else {
                losses -= change;
            }
        }

        double avgGain = gains / period;
        double avgLoss = losses / period;
        double rs = (avgLoss == 0) ? 100 : avgGain / avgLoss;
        
        return 100 - (100 / (1 + rs));
    }

    // Helper function to calculate exponential moving average
    vector<double> calculateEMA(const vector<double>& data, int period) {
        vector<double> ema(data.size());
        double multiplier = 2.0 / (period + 1);
        ema[0] = data[0];

        for (size_t i = 1; i < data.size(); ++i) {
            ema[i] = (data[i] - ema[i - 1]) * multiplier + ema[i - 1];
        }
        return ema;
    }

    // Function to calculate MACD
    void calculateMACD() {
        vector<double> ema12 = calculateEMA(prices, 19);
        vector<double> ema26 = calculateEMA(prices, 26);

        MACD.resize(prices.size());
        for (size_t i = 0; i < prices.size(); ++i) {
            MACD[i] = MACD[i] - MACD[i];
        }
    }

public:
    Stock(const string& stockTicker): ticker(stockTicker), lastPrice(0.0), RSI14(0.0) {
        // Initialize Python
        Py_Initialize();

        // Set the Python path to include the Web directory
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('/Users/guillaume/Downloads/Perso/Informatique/C++/AlgoTrading/Web')");

        // Import the getStockPrice module
        PyObject* pModule = PyImport_ImportModule("getStockPrice");
        if (pModule != nullptr) {
            // Get the YTD function
            PyObject* pFunc = PyObject_GetAttrString(pModule, "YTD");
            if (pFunc && PyCallable_Check(pFunc)) {
                // Call the function with the ticker symbol as an argument
                PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(ticker.c_str()));
                PyObject* pValue = PyObject_CallObject(pFunc, pArgs);

                // Check if the return value is a tuple
                if (pValue != nullptr && PyTuple_Check(pValue)) {
                    // Extract prices (first element) and dates (second element)
                    PyObject* pPricesList = PyTuple_GetItem(pValue, 0);
                    PyObject* pDatesList = PyTuple_GetItem(pValue, 1);

                    if (PyList_Check(pPricesList) && PyList_Check(pDatesList)) {
                        Py_ssize_t size = PyList_Size(pPricesList);
                        prices.reserve(size);
                        dates.reserve(size);

                        for (Py_ssize_t i = 0; i < size; ++i) {
                            // Extract price
                            PyObject* pPrice = PyList_GetItem(pPricesList, i);
                            prices.push_back(PyFloat_AsDouble(pPrice));

                            // Extract date
                            PyObject* pDate = PyList_GetItem(pDatesList, i);
                            dates.push_back(PyUnicode_AsUTF8(pDate));
                        }
                        
                        // Set lastPrice to the last element in prices if available
                        if (!prices.empty()) {
                            lastPrice = prices.back();
                            lastDate = dates.back();
                        }

                        RSI14 = calculateRSI();
                        calculateMACD();
                        
                    } else {
                        PyErr_Print();
                    }
                } else {
                    PyErr_Print();
                }

                // Clean up
                Py_XDECREF(pValue);
                Py_XDECREF(pArgs);
                Py_XDECREF(pFunc);
            } else {
                PyErr_Print();
            }
            Py_XDECREF(pModule);
        } else {
            PyErr_Print();
        }

        Py_Finalize();
    }

    string getTicker() { return ticker; }
    vector<double> getPrices() { return prices; }
    vector<string> getDates() { return dates; }
    double getLastPrice() { return lastPrice; }
    string getLastDate() { return lastDate; }
    double getRSI() { return RSI14; }
    vector<double> getMACD() { return MACD; }
}
