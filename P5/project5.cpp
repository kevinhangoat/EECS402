#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "SimulatorClass.h"
// #include "EventClass.h"
// #include "FIFOQueueClass.h"
// #include "LinkedNodeClass.h"
// #include "SortedListClass.h"
// #include "constants.h"
// #include "random.h"

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

// Program Header
// Programmer: Yutian Han
// Date: March 2020
// Purpose: EECS Project4


int main(int argc, char *argv[])
{
    // error checking for number of input files and read inputs
    if (argc != RIGHT_NUMBER_OF_INPUT)
    {
        cout << "Usage: ./proj5.exe <simParams.txt>" << endl;
        exit(EXIT_WRONG_NUMBER_OF_INPUT);
    }

    string inFileName = argv[IDX_INPUT_FILE];
    ifstream inFile;
    inFile.open(inFileName.c_str());


    if (inFile.eof())
    {
        cout << "Error: EOF before reading the file" << endl;
        return 0;
    }
    else if (inFile.fail())
    {
        inFile.clear();
        inFile.ignore(200, '\n');
        cout << "Error: Reading files" << endl;
        return 0;
    }

    SimulatorClass newSim (inFile, DEFAULT_CAR_SIZE, DEFAULT_NAME);

    //initialize the simulator
    int riderTime = 0;
    int carTime = 1;


    cout << endl;
    cout << "Sending first rider arrival and car arrival events!" << endl;
    cout << endl;
    cout << "============================================================="
         <<  endl;
    newSim.riderArrival(riderTime);
    cout << "============================================================="
         <<  endl;
    newSim.carArrival(carTime);
    cout << "============================================================="
         <<  endl;

    while (newSim.getEventSize() != EMPTY_LIST_SIZE ||
           !newSim.noRiderWaiting())
    {
        newSim.handleNextEvent(riderTime, carTime);
        cout << "============================================================="
             <<  endl;

    }
    newSim.performStatistics();

    return 0;
}

#endif
