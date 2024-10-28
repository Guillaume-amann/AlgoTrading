#include <iostream>
#include <Python.h>
using namespace std;

class Stock {
private:
    string ticker;
    vector<float> prices;

public:
    double lastPrice;
    Stock(const string& ticker) : ticker(ticker) {
        fetchYTDPrices();
        if (!prices.empty()) {
            lastPrice = prices.back();  // Set last_price as the most recent price
        } else {
            cerr << "Error: No prices available for ticker " << ticker << endl;
            lastPrice = -1;  // Indicate an error if no prices were fetched
        }
    }

    void fetchYTDPrices() {
        Py_Initialize();
        PyRun_SimpleString("import sys; sys.path.append('.')");

        PyObject* getStockPriceString = PyUnicode_FromString("Web.getStockPrice");
        PyObject* getStockPriceModule = PyImport_Import(getStockPriceString);
        Py_DECREF(getStockPriceString);

        PyObject* ytdFunction = PyObject_GetAttrString(getStockPriceModule, "YTD");
        PyObject* pyTicker = PyUnicode_FromString(ticker.c_str());
        PyObject* ytdArgs = PyTuple_Pack(1, pyTicker);
        Py_DECREF(pyTicker);

        PyObject* ytdResult = PyObject_CallObject(ytdFunction, ytdArgs);
        Py_DECREF(ytdArgs);
        Py_DECREF(ytdFunction);
        Py_DECREF(getStockPriceModule);

        // Fill `prices` vector with the last 252 values
        Py_ssize_t size = PyList_Size(ytdResult);
        prices.clear();
        for (Py_ssize_t i = 0; i < size; i++) {
            PyObject* item = PyList_GetItem(ytdResult, i);
            if (PyFloat_Check(item)) {
                prices.push_back(PyFloat_AsDouble(item));
            }
        }

        Py_DECREF(ytdResult);
        Py_Finalize();
    }

    double getLastPrice() const {
        return lastPrice;
    }

    const vector<float>& getPriceHistory() const {
        return prices;
    }
};