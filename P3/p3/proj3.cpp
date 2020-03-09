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




#ifdef ANDREW_TEST
#include "andrewTest.h"
#else


int main()
{
    // printMenu();
    string inFName = "deer.ppm";
    string outFName = "testDeer.ppm";

    ColorImageClass image;

    image.readPpmFile(inFName);
    image.writePpmFile(outFName);

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
