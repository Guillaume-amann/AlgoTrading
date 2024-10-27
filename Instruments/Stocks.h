#include <iostream>
#include <Python.h>
using namespace std;

class Stock {
private:
    string ticker;
    vector<string> dates;
    vector<float> prices;

public:
    double lastprice(string ticker) {
        Py_Initialize();
        PyRun_SimpleString("import sys; sys.path.append('.')");

        PyObject* getStockPriceString = PyUnicode_FromString("Web.getStockPrice");
        PyObject* getStockPriceModule = PyImport_Import(getStockPriceString);
        Py_DECREF(getStockPriceString);

        PyObject* getStockPriceFunction = PyObject_GetAttrString(getStockPriceModule, "get_last_stock_price");
        PyObject* pyTicker = PyUnicode_FromString(ticker.c_str());
        PyObject* getStockPriceArgs = PyTuple_Pack(1, pyTicker);
        Py_DECREF(pyTicker);

        PyObject* getStockPriceResult = PyObject_CallObject(getStockPriceFunction, getStockPriceArgs);
        Py_DECREF(getStockPriceFunction);

        if (!getStockPriceResult || !PyFloat_Check(getStockPriceResult)) {
            cerr << "Error fetching stock price." << endl;
        }

        double stcPrice = PyFloat_AsDouble(getStockPriceResult);
        return stcPrice << endl;
        Py_XDECREF(getStockPriceResult);
        Py_XDECREF(getStockPriceModule);
        Py_XDECREF(getStockPriceArgs);
    }





    PyObject* ytdFunction = PyObject_GetAttrString(getStockPriceModule, "YTD");
    if (!ytdFunction || !PyCallable_Check(ytdFunction)) {
        cerr << "Error: YTD function not found or not callable." << endl;
        Py_DECREF(getStockPriceModule);
        Py_Finalize();
        return 1;
    }

    PyObject* ytdResult = PyObject_CallObject(ytdFunction, getStockPriceArgs);
    Py_DECREF(getStockPriceArgs);
    Py_DECREF(ytdFunction);
    
    if (!PyList_Check(ytdResult)) {
        cerr << "Error: ytdResult is not a list." << endl;
        Py_DECREF(ytdResult);
        Py_DECREF(getStockPriceModule);
        Py_Finalize();
        return 1;
    }







    Py_ssize_t size = PyList_Size(ytdResult);
    vector<double> ytd_prices;
    for (Py_ssize_t i = 0; i < size; i++) {
        PyObject* item = PyList_GetItem(ytdResult, i);
        ytd_prices.push_back(PyFloat_AsDouble(item));
    }






    def get_last_stock_price(ticker):
    try:
        stock = yf.Ticker(ticker)
        hist = stock.history(period="1d")
        last_price = hist['Close'].iloc[-1]
        return last_price
    except Exception as e:
        print(f"Error fetching stock data: {e}")
        return None

def YTD(ticker):
    try:
        stock = yf.Ticker(ticker)
        hist = stock.history(period="1y")
        # Check if there are at least 252 entries
        if len(hist) >= 252:
            return list(hist['Close'].iloc[-252:])  # Return the last 252 prices
        else:
            print(f"Warning: Only {len(hist)} trading days available.")
            return list(hist['Close'])  # Return all available prices if less than 252
    except Exception as e:
        print(f"Error fetching YTD stock data: {e}")
        return None
};