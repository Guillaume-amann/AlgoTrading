#include <iostream>
#include <vector>
#include <Python.h>
#include "Regressors/Volatility.h"
using namespace std;

int main() {
    string ticker;
    cout << "Enter stock ticker: ";
    cin >> ticker;
    
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
    cout << "The stock price for " << ticker << " is: " << stcPrice << endl;
    Py_XDECREF(getStockPriceResult);

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
    double histVol = hist_vol(ytd_prices, "y");
    double histVolB = hist_vol(ytd_prices, "y", "bootstrap");

    string message = "The stock price of " + ticker + " is $" + to_string(stcPrice) + "\nPast year Historical Volatility: " + to_string(histVol) + " %"
                                                                                    + "\nPast year Historical Volatility (bootstrap): " + to_string(histVolB) + " %"
                                                                                    + "\n \n See more here: https://github.com/Guillaume-amann/AlgoTrading";

    //Now send an email if...
    if (stcPrice > 200) {
        cout << "Stock price is greater than 200, sending email..." << endl;

        PyObject* emailModuleString = PyUnicode_FromString("Web.email_sender");
        PyObject* emailModule = PyImport_Import(emailModuleString);
        Py_DECREF(emailModuleString);

        PyObject* sendEmailFunction = PyObject_GetAttrString(emailModule, "send_email");
        PyObject* pySender = PyUnicode_FromString("amann.guill@gmail.com"); // Replace with sender
        PyObject* pyRecipient = PyUnicode_FromString("amann.guill@gmail.com"); // Replace with recipient
        PyObject* pySubject = PyUnicode_FromString("Stock Price Alert");
        PyObject* pyBody = PyUnicode_FromString(message.c_str());
        PyObject* pyPassword = PyUnicode_FromString("");  // Replace with your app password
        PyObject* emailArgs = PyTuple_Pack(5, pySender, pyRecipient, pySubject, pyBody, pyPassword);
        Py_DECREF(pySender);
        Py_DECREF(pyRecipient);
        Py_DECREF(pySubject);
        Py_DECREF(pyBody);
        Py_DECREF(pyPassword);

        PyObject* emailResult = PyObject_CallObject(sendEmailFunction, emailArgs);
        Py_DECREF(emailArgs);

        if (!emailResult) {
            cerr << "Error: Failed to send email." << endl;
        } else {
            cout << "Email sent successfully!" << endl;
        }

        Py_DECREF(emailResult);
        Py_DECREF(sendEmailFunction);
        Py_DECREF(emailModule);
    }

    Py_DECREF(ytdResult);
    Py_DECREF(getStockPriceModule);
    Py_Finalize();
    return 0;
}