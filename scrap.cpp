#include <iostream>
#include <vector>
#include <Python.h>
#include "Regressors/Bootstrap.h"
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
    Py_DECREF(getStockPriceArgs);
    Py_DECREF(getStockPriceFunction);

    if (getStockPriceResult && PyFloat_Check(getStockPriceResult)) {
        double result = PyFloat_AsDouble(getStockPriceResult);
        cout << "The stock price for " << ticker << " is: " << result << endl;
        
        PyObject* ytdFunction = PyObject_GetAttrString(getStockPriceModule, "YTD");
        PyObject* ytdArgs = PyTuple_Pack(2, pyTicker);
        PyObject* ytdResult = PyObject_CallObject(ytdFunction, ytdArgs);
        Py_DECREF(ytdArgs);
        Py_DECREF(ytdFunction);

        if (ytdResult) {
            cout << "YTD function executed successfully." << endl;
            
            if (PyList_Check(ytdResult)) {
                vector<double> ytd_prices;
                Py_ssize_t size = PyList_Size(ytdResult);
                cout << "Size of YTD result: " << size << endl;

                for (Py_ssize_t i = 0; i < size; i++) {
                    PyObject* item = PyList_GetItem(ytdResult, i);

                    if (PyFloat_Check(item)) {
                        ytd_prices.push_back(PyFloat_AsDouble(item));
                    } else {
                        cerr << "Warning: Item at index " << i << " is not a float." << endl;
                    }
                }

                cout << "The last 252 stock prices for " << ticker << " are:" << endl;

                for (double price : ytd_prices) {
                    cout << price << " ";
                }

                cout << endl;
                string histVolResult = hist_vol(ytd_prices, "y");
                string message = "The stock price of " + ticker + " is $" + to_string(result) + histVolResult;

                //Now send an email if...
                if (result > 200) {
                    cout << "Stock price is greater than 250, sending email..." << endl;

                    PyObject* emailModuleString = PyUnicode_FromString("Web.email_sender");
                    PyObject* emailModule = PyImport_Import(emailModuleString);
                    Py_DECREF(emailModuleString);

                    PyObject* sendEmailFunction = PyObject_GetAttrString(emailModule, "send_email");
                    PyObject* pySender = PyUnicode_FromString("amann.guill@gmail.com"); // Replace with sender
                    PyObject* pyRecipient = PyUnicode_FromString("amann.guill@gmail.com"); // Replace with recipient
                    PyObject* pySubject = PyUnicode_FromString("Stock Price Alert");
                    PyObject* pyBody = PyUnicode_FromString(message.c_str());
                    PyObject* pyPassword = PyUnicode_FromString("cizbtmoesolhbiyf");  // Replace with your app password
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
            } else {
                cerr << "YTD function did not return a list." << endl;
            }
            Py_DECREF(ytdResult);
        } else {
            cerr << "Error fetching YTD stock prices." << endl;
        }
    } else {
        cerr << "Error fetching stock price." << endl;
    }

    Py_XDECREF(getStockPriceResult);
    Py_DECREF(getStockPriceModule);
    Py_Finalize();
    return 0;
}