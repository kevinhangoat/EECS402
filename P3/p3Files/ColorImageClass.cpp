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
    for (int rowIdx = 0; rowIdx < IMAGE_ROW_SIZE; rowIdx++)
    {
        for (int colIdx = 0; colIdx < IMAGE_COL_SIZE; colIdx ++)
        {
            ColorClass newPixel;
            newPixel.setToBlack();
            colorPixelArray[rowIdx][colIdx] = newPixel;
        }
    }
}

bool ColorImageClass::checkRowCol(RowColumnClass &inRowCol)
{
    return inRowCol.getRow() < IMAGE_ROW_SIZE &&
           inRowCol.getRow() >= 0             &&
           inRowCol.getCol() < IMAGE_COL_SIZE &&
           inRowCol.getCol() >= 0;
}

void ColorImageClass::initializeTo(ColorClass &inColor)
{
    for (int rowIdx = 0; rowIdx < IMAGE_ROW_SIZE; rowIdx++)
    {
        for (int colIdx = 0; colIdx < IMAGE_COL_SIZE; colIdx ++)
        {
            colorPixelArray[rowIdx][colIdx] = inColor;
        }
    }
}

//RESUBMISSION CODE UPDATE
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
    bool flagAddImageToNeedClipping = false;

    for (int rowIdx = 0; rowIdx < IMAGE_ROW_SIZE; rowIdx++)
    {
        for (int colIdx = 0; colIdx < IMAGE_COL_SIZE; colIdx ++)
        {
            RowColumnClass rowColToAdd (rowIdx, colIdx);

            ColorClass colorToAdd;
            rhsImg.getColorAtLocation(rowColToAdd, colorToAdd);

            // set new pixel to the original color
            ColorClass newPixel = colorPixelArray[rowIdx][colIdx];

            // add color to the pixel
            if (newPixel.addColor(colorToAdd))
            {
                flagAddImageToNeedClipping = true;
            }

            colorPixelArray[rowIdx][colIdx] = newPixel;
        }
    }
    return flagAddImageToNeedClipping;
}

bool ColorImageClass::addImages(int numImgsAdd,
                                ColorImageClass imagesToAdd [])
{
    bool flagAddImagesNeedClipping = false;

    for (int rowIdx = 0; rowIdx < IMAGE_ROW_SIZE; rowIdx++)
    {
        for (int colIdx = 0; colIdx < IMAGE_COL_SIZE; colIdx ++)
        {
            ColorClass newPixel;
            newPixel.setToBlack();

            for (int imgIdx = 0; imgIdx < numImgsAdd; imgIdx ++)
            {
                ColorImageClass imageToAdd = imagesToAdd[imgIdx];
                RowColumnClass rowColToAdd (rowIdx, colIdx);
                ColorClass colorToAdd;

                imageToAdd.getColorAtLocation(rowColToAdd, colorToAdd);

                if (newPixel.addColor(colorToAdd))
                {
                    flagAddImagesNeedClipping = true;
                }
                colorPixelArray[rowIdx][colIdx] = newPixel;
            }
        }
    }
    return flagAddImagesNeedClipping;
}

bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &inColor)
{
    if (checkRowCol(inRowCol))
        {
            colorPixelArray[inRowCol.getRow()][inRowCol.getCol()] = inColor;
            return true;
        }
    return false;
}

bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &outColor)
{
    if (checkRowCol(inRowCol))
        {
            outColor = colorPixelArray[inRowCol.getRow()][inRowCol.getCol()];
            return true;
        };
    return false;
}

void ColorImageClass::printImage()
{
    for (int rowIdx = 0; rowIdx < IMAGE_ROW_SIZE; rowIdx++)
    {
        for (int colIdx = 0; colIdx < IMAGE_COL_SIZE; colIdx++)
        {
            if (colIdx != 0)
            {
                cout << "--";
            }
            ColorClass newColorToPrint = colorPixelArray[rowIdx][colIdx];
            newColorToPrint.printComponentValues();
        }
        cout << endl;
    }
}


// Funtions below are for the PPM image reading

// bool ColorImageClass::readValueRow(ifstream &inFile, bool &validFileFound,
//                                    const int rowIdx, const int colNum)
// {
//     for (int colIdx = 0; colIdx < colNum; colIdx += 3)
//     {
//         ColorClass pixel;
//         pixel.readValueRGB(inFile);
//         colorPixelArray[rowIdx][colIdx] = pixel;
//     }
//     return !inFile.fail();
// }


// bool ColorImageClass::readPpmPixels(ifstream &inFile, bool &validFileFound,
//                                     RowColumnClass &inFileWidthHeight)
// {
//     int rowNum = inFileWidthHeight.getRow();
//     int colNum = inFileWidthHeight.getCol();
//     for (int rowIdx = 0; rowIdx < rowNum && validFileFound; rowIdx ++)
//     {
//         validFileFound = readValueRow(inFile, validFileFound, rowIdx, colNum);
//     }
//     return validFileFound;
// }

// bool ColorImageClass::readPpmFile(const string &inFname)
// {
//     ifstream inFile;
//     inFile.open(inFname.c_str());

//     //error checking: check if the file can be read
//     if (inFile.fail())
//     {
//         cout << "Unable to open input file!" << endl;
//         exit(EXIT_ERROR_UNABLE_TO_OPEN);
//     }

//     bool validFileFound = true;
//     string magicNum;
//     RowColumnClass inFileWidthHeight;
//     int maxVal;


//     readPpmMagicNum(inFile, validFileFound, magicNum);
//     readPpmHeightWidth(inFile, validFileFound, inFileWidthHeight);
//     readPpmMaxVal(inFile, validFileFound, maxVal);
//     // readPpmPixels(inFile, validFileFound, inFileWidthHeight);

//     return true;
//     // for (int rowIdx = 0;
//     //     rowIdx < MAT_ROWS && success;
//     //     rowIdx++)
//     //     {
//     //     success = readValueRow(inFile, rowIdx);
//     //     //maybe some more here!
//     //     }
// }
