#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "constants.h"
#include "MessageClass.h"


MessageClass::MessageClass()
{
    validFileFound = false;
}


int** MessageClass::getMessageMatrix()
{
    return messageMatrix;
}


int MessageClass::getMessageRowSize()
{
    return messageRowSize;
}


int MessageClass::getMessageColSize()
{
    return messageColSize;
}


bool MessageClass::readMessageFile(const string &inFname)
{
    ifstream inFile;
    inFile.open(inFname.c_str());

    //error checking: check if the file can be read
    if (inFile.fail())
    {
        cout << "Unable to open input file!" << endl;
        return false;
        exit(EXIT_ERROR_UNABLE_TO_OPEN);
    }

    inFile >> messageColSize;
    inFile >> messageRowSize;
    messageMatrix = new int*[messageRowSize];
    for (int rowIdx = 0; rowIdx < messageRowSize; rowIdx++)
    {
        messageMatrix[rowIdx] = new int[messageColSize];
    }

    for (int rowIdx = 0; rowIdx < messageRowSize; rowIdx++)
    {
        for (int colIdx = 0; colIdx < messageColSize; colIdx ++)
        {
            validFileFound = false;
            while (!validFileFound)
            {
                inFile >> messageMatrix[rowIdx][colIdx];
                if (inFile.eof())
                {
                    cout << "Error: Message file has the wrong size" << endl;
                    return validFileFound;
                }
                else if (inFile.fail())
                {
                    inFile.clear();
                    inFile.ignore(200, '\n');
                    cout << "Error: Reading message value at row/col: "
                     << rowIdx << " "
                     << colIdx << " " << endl;
                     return validFileFound;
                }
                else
                {
                    validFileFound = true;
                }
            }
        }
    }
    inFile.close();
    return validFileFound;
}

bool MessageClass::writeMessageFile(const string &outFname)
{
    ofstream outFile;
    outFile.open(outFname.c_str());

    //error checking: check if the file can be read
    if (outFile.fail())
    {
        cout << "Unable to open output file!" << endl;
        exit(EXIT_ERROR_UNABLE_TO_OPEN);
    }

    outFile << messageColSize << " " << messageRowSize << endl;
    for (int rowIdx = 0; rowIdx < messageRowSize; rowIdx ++)
    {
        for (int colIdx = 0; colIdx < messageColSize; colIdx ++)
        {
            outFile << messageMatrix[rowIdx][colIdx] << " ";
        }
        outFile << endl;
    }
    outFile.close();
    return true;
}
