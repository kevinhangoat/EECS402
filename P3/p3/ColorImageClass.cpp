#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "constants.h"

// ColorImageclass functions:

ColorImageClass::ColorImageClass()
{

}


// Funtions below are for the PPM image reading

bool ColorImageClass::readPpmMagicNum(ifstream &inFile, bool &validFileFound,
                                      string &magicNum)
{
    if (inFile.eof())
    {
        cout << "EOF before magic number" << endl;
        validFileFound = false;
        return validFileFound;
    }
    inFile >> magicNum;
    return validFileFound;
}

bool ColorImageClass::readPpmHeightWidth(ifstream &inFile,
                                         bool &validFileFound,
                                         int &imageRowSize, int &imageColSize)
{
    if (inFile.eof())
    {
        cout << "EOF before height width information" << endl;
        validFileFound = false;
        return validFileFound;
    }

    inFile >> imageColSize;
    inFile >> imageRowSize;

    return validFileFound;
}

bool ColorImageClass::readPpmMaxVal(ifstream &inFile, bool &validFileFound,
                                    int &maxVal)
{
    if (inFile.eof())
    {
        cout << "EOF before max value information" << endl;
        validFileFound = false;
        return validFileFound;
    }

    inFile >> maxVal;
    return validFileFound;
}

bool ColorImageClass::readPpmFile(const string &inFname)
{
    ifstream inFile;
    inFile.open(inFname.c_str());

    //error checking: check if the file can be read
    if (inFile.fail())
    {
        cout << "Unable to open input file!" << endl;
        exit(EXIT_ERROR_UNABLE_TO_OPEN);
    }

    readPpmMagicNum(inFile, validFileFound, magicNum);
    readPpmHeightWidth(inFile, validFileFound, imageRowSize, imageColSize);
    readPpmMaxVal(inFile, validFileFound, maxVal);
    readPpmPixels(inFile, validFileFound, imageRowSize, imageColSize);
    inFile.close();
    // cout << magicNum << endl << imageRowSize << endl << imageColSize;
    return true;
}

bool ColorImageClass::readPpmPixels(ifstream &inFile, bool &validFileFound,
                                    const int imageRowSize,
                                    const int imageColSize)
{
    colorPixelArray = new ColorClass*[imageRowSize];
    for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx++)
    {
        colorPixelArray[rowIdx] = new ColorClass[imageColSize];
    }

    for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx++)
    {
        for (int colIdx = 0; colIdx < imageColSize; colIdx ++)
        {
            colorPixelArray[rowIdx][colIdx].readValueRGB(inFile);
        }
    }
    // for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx++)
    // {
    //     delete [] colorPixelArray[rowIdx];
    // }
    // delete [] colorPixelArray;
    return true;
}

bool ColorImageClass::writePpmPixels(ofstream &outFile,
                                     const int imageRowSize,
                                     const int imageColSize)
{
    // cout << colorPixelArray[0][0].redComp << " "
    //      << colorPixelArray[0][0].greenComp << " "
    //      << colorPixelArray[0][0].blueComp << endl;
    for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx ++)
    {
        for (int colIdx = 0; colIdx < imageColSize; colIdx ++)
        {
            colorPixelArray[rowIdx][colIdx].writeValueRGB(outFile);
            // outFile << colorPixelArray[rowIdx][colIdx].redComp << " ";
            // outFile << colorPixelArray[rowIdx][colIdx].greenComp << " ";
            // outFile << colorPixelArray[rowIdx][colIdx].blueComp << " ";
        }
        outFile << endl;
    }
    outFile.close();
    return true;
}

bool ColorImageClass::writePpmFile(const string &outFname)
{
    ofstream outFile;
    outFile.open(outFname.c_str());

    //error checking: check if the file can be read
    if (outFile.fail())
    {
        cout << "Unable to open output file!" << endl;
        exit(EXIT_ERROR_UNABLE_TO_OPEN);
    }

    outFile << magicNum << endl;
    outFile << imageColSize << " " << imageRowSize << endl;
    outFile << maxVal << endl;
    writePpmPixels(outFile, imageRowSize, imageColSize);
    return true;
}
