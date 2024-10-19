#include <iostream>
#include <Python.h>
using namespace std;

int main() {
    Py_Initialize();
    PyRun_SimpleString("import sys; sys.path.append('.')");

    string ticker;
    cout << "Enter stock ticker: ";
    cin >> ticker;

    PyObject* myModuleString = PyUnicode_FromString("Web.getStockPrice");
    PyObject* myModule = PyImport_Import(myModuleString);
    Py_DECREF(myModuleString);

    PyObject* getDataFunction = PyObject_GetAttrString(myModule, "get_last_stock_price");
    PyObject* pyTicker = PyUnicode_FromString(ticker.c_str());
    PyObject* args = PyTuple_Pack(1, pyTicker);
    Py_DECREF(pyTicker);

    PyObject* myResult = PyObject_CallObject(getDataFunction, args);
    Py_DECREF(args);

    if (myResult && PyFloat_Check(myResult)) {
        double result = PyFloat_AsDouble(myResult);
        cout << "The stock price for " << ticker << " is: " << result << endl;

        if (result > 200) {
            cout << "Stock price is greater than 250, sending email..." << endl;

            PyObject* emailModuleString = PyUnicode_FromString("Web.email_sender");
            PyObject* emailModule = PyImport_Import(emailModuleString);
            Py_DECREF(emailModuleString);

            PyObject* sendEmailFunction = PyObject_GetAttrString(emailModule, "send_email");

            PyObject* pySender = PyUnicode_FromString("XXXXX"); // Replace with sender
            PyObject* pyRecipient = PyUnicode_FromString("XXXXX"); // Replace with recipient
            PyObject* pySubject = PyUnicode_FromString("Stock Price Alert");
            string message = "The stock price of " + ticker + " is $" + to_string(result);
            PyObject* pyBody = PyUnicode_FromString(message.c_str());
            PyObject* pyPassword = PyUnicode_FromString("XXXXX");  // Replace with your app password

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

    }

    Py_XDECREF(myResult);
    Py_DECREF(myFunction);
    Py_DECREF(myModule);

    Py_Finalize();
    return 0;
}