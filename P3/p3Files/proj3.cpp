#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "constants.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"




// Program Header
// Programmer: Yutian Han
// Date: March 2020
// Purpose: EECS Project3


// print the bsaic menu on the terminal
// no input and output
void printMenu();

// input a filestream and handle the bad input
// input: the file name string
// output:
string inputValidFileStream();

// A private function read the magic number of PPM
// input: input file stream, a boolean showing if the input
//        file is valid and the magic number
// output: a boolean showing if the input file is valid
bool readPpmMagicNum(ifstream &inFile, bool &validFileFound,
                     string &magicNum);

// A private function read the height and width of the PPM
// input: input file stream, a boolean showing if the input
//        file is valid and the row col class
// output: a boolean showing if the input file is valid
bool readPpmHeightWidth(ifstream &inFile, bool &validFileFound,
                        RowColumnClass &inFileWidthHeight);

// A private function read the maximum value of the PPM
// input: input file stream, a boolean showing if the input
//        file is valid and the maximum value
// output: a boolean showing if the input file is valid
bool readPpmMaxVal(ifstream &inFile, bool &validFileFound, int &maxVal);


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else


int main()
{
    // printMenu();
    string fileName;
    fileName = "deer.ppm";
    ifstream inFile;
    inFile.open(fileName.c_str());

    //error checking: check if the file can be read
    if (inFile.fail())
    {
        cout << "Unable to open input file!" << endl;
        exit(EXIT_ERROR_UNABLE_TO_OPEN);
    }

    bool validFileFound = true;
    string magicNum;
    RowColumnClass inFileWidthHeight;
    int maxVal;

    readPpmMagicNum(inFile, validFileFound, magicNum);
    readPpmHeightWidth(inFile, validFileFound, inFileWidthHeight);
    readPpmMaxVal(inFile, validFileFound, maxVal);

    // ColorImageClass *newImage = new ColorImageClass;
    // newImage->imageRowSize = inFileWidthHeight.getRow();
    // newImage->imageColSize = inFileWidthHeight.getCol();
    // newImage.printImage();
    // cout << image.readPpmFile(fileName) << endl;
    // image.printImage();
    return 0;
}



#endif


void printMenu()
{
    cout << ENCODE_OPTION
         << ". Encode a message from file" << endl;
    cout << DECODE_OPTION
         << ". Perform decode" << endl;
    cout << WRITE_OPTION
         << ". Write current image to file" << endl;
    cout << EXIT_OPTION << ". Exit the program" << endl;
    cout << "Enter your choice:";
}


bool readPpmMagicNum(ifstream &inFile, bool &validFileFound,
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

bool readPpmHeightWidth(ifstream &inFile,
                        bool &validFileFound,
                        RowColumnClass &inFileWidthHeight)
{
    if (inFile.eof())
    {
        cout << "EOF before height width information" << endl;
        validFileFound = false;
        return validFileFound;
    }

    int listHeightWidth[PPM_DIMENSION];
    for (int dimInd = 0;
         dimInd < PPM_DIMENSION;
         dimInd++)
    {
        inFile >> listHeightWidth[dimInd];
    }
    inFileWidthHeight.setRow(listHeightWidth[HEIGHT_IDX]);
    inFileWidthHeight.setCol(listHeightWidth[WIDTH_IDX]);
    return validFileFound;
}

bool readPpmMaxVal(ifstream &inFile, bool &validFileFound,
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









// const int MAT_ROWS = 4;
// const int MAT_COLS = 5;
// class MatrixInfo
// {
//     private:
//         int matrixVals[MAT_ROWS][MAT_COLS];
//         bool readHeaderRow(ifstream &inFile)
//         {
//             string headerVal;
//             for (int colInd = 0;
//                  colInd < MAT_COLS;
//                  colInd++)
//             {
//                 inFile >> headerVal;
//             }
//             return !inFile.fail();
//         }


//         bool readValueRow(ifstream &inFile,
//         const int rowInd)
//         {
//             for (int colInd = 0;
//             colInd < MAT_COLS;
//             colInd++)
//             {
//             inFile >> matrixVals[rowInd][colInd];
//             }
//             return !inFile.fail();
//         }

    // public:
    //     bool readMatrixFile(const string &inFname)
    //     {
    //         bool success;
    //         ifstream inFile;
    //         inFile.open(inFname.c_str());
    //         //error checking here!
    //         success = readHeaderRow(inFile);
    //         //probably more error checking here!
    //         for (int rowInd = 0;
    //              rowInd < MAT_ROWS && success;
    //              rowInd++)
    //         {
    //             success = readValueRow(inFile, rowInd);
    //         //maybe some more here!
    //         }
    //         inFile.close();
    //     }
