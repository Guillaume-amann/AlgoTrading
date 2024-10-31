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

public:
    Stock(const string& stockTicker) : ticker(stockTicker), lastPrice(0.0) {
        // Initialize Python
        Py_Initialize();

        // Set the Python path to include the Web directory
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('/Users/guillaume/Downloads/Perso/Informatique/C++/AlgoTrading/Web/')");

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

    string getTicker() { return ticker; };
    vector<double> getPrices() { return prices; };
    vector<string> getDates() { return dates; };
    double getLastPrice() { return lastPrice; };
    string getLastDate() { return lastDate; };
};