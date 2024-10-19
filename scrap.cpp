#include <iostream>
#include <Python.h>
using namespace std;

int main() {
    // Initialize the Python interpreter
    Py_Initialize();
    PyRun_SimpleString("import sys; sys.path.append('.')");

    string ticker;
    cout << "Enter stock ticker: ";
    cin >> ticker;

    // Import the Python module
    PyObject* myModuleString = PyUnicode_FromString("DataDownloader.getStockPrice");
    PyObject* myModule = PyImport_Import(myModuleString);
    Py_DECREF(myModuleString);

    if (!myModule) {
        cerr << "Error: Failed to load Python module." << endl;
        Py_Finalize();
        return 1;
    }

    // Get the function from the module
    PyObject* myFunction = PyObject_GetAttrString(myModule, "get_last_stock_price");
    if (!myFunction || !PyCallable_Check(myFunction)) {
        cerr << "Error: Function not found or not callable." << endl;
        Py_DECREF(myModule);
        Py_Finalize();
        return 1;
    }

    // Prepare the argument
    PyObject* pyTicker = PyUnicode_FromString(ticker.c_str());
    PyObject* args = PyTuple_Pack(1, pyTicker);
    Py_DECREF(pyTicker);

    // Call the function
    PyObject* myResult = PyObject_CallObject(myFunction, args);
    Py_DECREF(args);

    if (myResult && PyFloat_Check(myResult)) {
        double result = PyFloat_AsDouble(myResult);
        cout << "The stock price for " << ticker << " is: " << result << endl;  // Print the stock price
    } else {
        cerr << "Error: Unexpected return type from Python function." << endl;
    }

    // Clean up Python objects
    Py_XDECREF(myResult);
    Py_DECREF(myFunction);
    Py_DECREF(myModule);

    // Finalize the Python interpreter
    Py_Finalize();
    return 0;
}