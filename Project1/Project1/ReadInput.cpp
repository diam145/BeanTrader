// ReadInput.cpp
#include "ReadInput.h"

void readStringInput(string info, string* buff) {
    buff->clear();

    cout << info;

    while (!(cin >> *buff)) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter a valid input: ";
    }
}
