#include <iostream>
#include <cstring>
#include "Exceptions.h"
#include <cstring>

using namespace std;

string Exceptions::error(int error) {
    string err_text = "\n-------------------------\nERROR. ";
    switch (error) {
        case FEW_POINTS:
            err_text = err_text + "Too few points to interpolate. Minimum is:\n\t"
                                  "• 4 for Akima Spline;\n\t"
                                  "• 2 for Cubic Spline;";
            break;
        case FILE_ERROR:
            err_text = err_text + "Error reading from file. Check if:\n\t"
                                  "• File name spelling is right;\n\t"
                                  "• File exists;";
            break;
        default:
            err_text = err_text + "Unknown Error";
            break;
    }
    err_text = err_text + "\n-------------------------\n";
    cout << err_text << endl;
    return err_text;
}
