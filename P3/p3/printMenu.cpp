#include <iostream>
using namespace std;
#include "printMenu.h"
#include "constants.h"

void printMenu()
{
    cout << ENCODE_OPTION
         << ". Encode a message from file" << endl;
    cout << DECODE_OPTION
         << ". Perform decode" << endl;
    cout << WRITE_OPTION
         << ". Write current image to file" << endl;
    cout << EXIT_OPTION << ". Exit the program" << endl;
    cout << "Enter your choice: ";
}
