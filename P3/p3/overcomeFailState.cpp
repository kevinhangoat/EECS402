#include <iostream>
using namespace std;
#include "overcomeFailState.h"

int overcomeFailState(int &inState)
{
    bool validInputFound;
    validInputFound = false;
    while (!validInputFound)
    {
        cin >> inState;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(200, '\n');
            cout << "Fail state!" << endl;
            cout << "Try again (Enter a positive integer): ";
        }
        else
        {
            validInputFound = true;
        }
    }
    return inState;
}
