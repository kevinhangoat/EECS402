#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "constants.h"
#include "MessageClass.h"


ColorImageClass::ColorImageClass()
{
    validFileFound = false;
}



bool ColorImageClass::readPpmMagicNum(ifstream &inFile, bool &validFileFound,
                                      string &magicNum)
{
    validFileFound = false;
    while (!validFileFound)
    {
        if (inFile.eof())
        {
            cout << "Error: EOF before magic number" << endl;
            return validFileFound;
        }
        else if (inFile.fail())
        {
            inFile.clear();
            inFile.ignore(200, '\n');
            cout << "Error: Reading magic number" << endl;
             return validFileFound;
        }
        else
        {
            validFileFound = true;
        }
    }
    inFile >> magicNum;
    return validFileFound;
}



bool ColorImageClass::readPpmHeightWidth(ifstream &inFile,
                                         bool &validFileFound,
                                         int &imageRowSize, int &imageColSize)
{
    validFileFound = false;
    while (!validFileFound)
    {
        if (inFile.eof())
        {
            cout << "Error: EOF before height width information" << endl;
            return validFileFound;
        }
        else if (inFile.fail())
        {
            inFile.clear();
            inFile.ignore(200, '\n');
            cout << "Error: Reading PPM height and width" << endl;
            return validFileFound;
        }
        else
        {
            validFileFound = true;
        }
    }

    inFile >> imageColSize;
    inFile >> imageRowSize;

    if (imageColSize > MAXIMUM_ROW_COL_SIZE ||
        imageRowSize > MAXIMUM_ROW_COL_SIZE)
    {
        cout << "The input image size is bigger than " << MAXIMUM_ROW_COL_SIZE
             << "x" << MAXIMUM_ROW_COL_SIZE << endl;
        validFileFound = false;
    }
    return validFileFound;
}



bool ColorImageClass::readPpmMaxVal(ifstream &inFile, bool &validFileFound,
                                    int &maxVal)
{
    validFileFound = false;
    while (!validFileFound)
    {
        if (inFile.eof())
        {
            cout << "Error: EOF before PPM maximum value" << endl;
            return validFileFound;
        }
        else if (inFile.fail())
        {
            inFile.clear();
            inFile.ignore(200, '\n');
            cout << "Error: Reading PPM maximum value" << endl;
            return validFileFound;
        }
        else
        {
            validFileFound = true;
        }
    }

    inFile >> maxVal;
    return validFileFound;
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
            if (!colorPixelArray[rowIdx][colIdx].readValueRGB(inFile))
            {
                cout << "Error: Reading image pixel at row: "
                     << rowIdx << "  col: " << colIdx << endl;
                validFileFound = false;
                return validFileFound;
            }
        }
    }
    // for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx++)
    // {
    //     delete [] colorPixelArray[rowIdx];
    // }
    // delete [] colorPixelArray;
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

    if (!readPpmMagicNum(inFile, validFileFound, magicNum))
    {
        return validFileFound;
    }
    if (!readPpmHeightWidth(inFile, validFileFound, imageRowSize, imageColSize))
    {
        return validFileFound;
    }
    if (!readPpmMaxVal(inFile, validFileFound, maxVal))
    {
        return validFileFound;
    }
    if (!readPpmPixels(inFile, validFileFound, imageRowSize, imageColSize))
    {
        return validFileFound;
    }
    inFile.close();
    return validFileFound;
}



bool ColorImageClass::writePpmPixels(ofstream &outFile,
                                     const int imageRowSize,
                                     const int imageColSize)
{
    for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx ++)
    {
        for (int colIdx = 0; colIdx < imageColSize; colIdx ++)
        {
            colorPixelArray[rowIdx][colIdx].writeValueRGB(outFile);
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



void ColorImageClass::decodePpmFile()
{
    for (int rowIdx = 0; rowIdx < imageRowSize; rowIdx ++)
    {
        for (int colIdx = 0; colIdx < imageColSize; colIdx ++)
        {
            colorPixelArray[rowIdx][colIdx].decodePixel();
        }
    }
    cout << "Image modified to decoded image contents" << endl;

}



bool ColorImageClass::encodePpmFile(RowColumnClass upperLeftLocation,
                                    MessageClass &encodingMessage)
{
    int messageRowSize = encodingMessage.getMessageRowSize();
    int messageColSize = encodingMessage.getMessageColSize();
    int** messageMatrix = encodingMessage.getMessageMatrix();
    int startRowVal = upperLeftLocation.getRow();
    int startColVal = upperLeftLocation.getCol();
    bool isEncodeSuccessful = true;

    for (int rowIdx = startRowVal;
         rowIdx < min(startRowVal + messageRowSize, imageRowSize);
         rowIdx ++)
    {
        for (int colIdx = startColVal;
             colIdx < min(startColVal + messageColSize, imageColSize);
             colIdx ++)
        {
            int encodingVal
                = messageMatrix[rowIdx - startRowVal][colIdx - startColVal];

            if (!colorPixelArray[rowIdx][colIdx].encodePixel(encodingVal))
            {
                isEncodeSuccessful = false;
                return isEncodeSuccessful;
            }
        }
    }
    return isEncodeSuccessful;
}
