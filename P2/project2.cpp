#include <iostream>
using namespace std;



// Program Header
// Programmer: Yutian Han
// Date: February 2020
// Purpose: EECS Project2; Create three classes: ColorClass, RowColumnClass and
//          ColorImageClass and their class functions for further use



const int ALLOWED_COLOR_MINIMUM = 0;
const int ALLOWED_COLOR_MAXIMUM = 1000;
const int RED_INDEX = 0;
const int GREEN_INDEX = 1;
const int BLUE_INDEX = 2;
const int NUMBER_OF_COLOR_COMPS = 3;
const int DEFAULT_ROW_COL = -99999;
const int IMAGE_ROW_SIZE = 1000;
const int IMAGE_COL_SIZE = 1000;



//ColorClass contains information (RGB values) describing a color
class ColorClass
{
    private:
        int redComp;
        int greenComp;
        int blueComp;

        // A private function to check if clipping is needed and clip colors.
        // If the color class has color components being out of the range, it
        // will clip the color and return true. Otherwise, do nothing and
        // return false
        // input: N/A
        // output: true if clipping is necessary, false if otherwise
        bool clipColorComps();

    public:
        // Default constructor
        // input: N/A
        // output: N/A
        ColorClass();

        // Default constructor
        // input: 3 integers for the RGB values respectively
        // output: N/A
        ColorClass(int inRed, int inGreen, int inBlue);

        // Set the color to black
        // input: N/A
        // output: N/A
        void setToBlack();

        // Set the color to red
        // input: N/A
        // output: N/A
        void setToRed();

        // Set the color to green
        // input: N/A
        // output: N/A
        void setToGreen();

        // Set the color to blue
        // input: N/A
        // output: N/A
        void setToBlue();

        // Set the color to white
        // input: N/A
        // output: N/A
        void setToWhite();

        // Set the RGB value to the provided values
        // input: red, green, glue element value
        // output: true if clipping is necessary, false if otherwise
        bool setTo(int inRed, int inGreen, int inBlue);

        // Set the component color values the same as those in the input
        // color class
        // input: a ColorClass
        // output: true if clipping is necessary, false if otherwise
        bool setTo(ColorClass &inColor);

        // Add the corresponding component color values of the input color to
        // the color class
        // input: a ColorClass
        // output: true if clipping is necessary, false if otherwise
        bool addColor(ColorClass &rhs);

        // Subtract the corresponding component color values of the input color
        // to the color class
        // input: a ColorClass
        // output: true if clipping is necessary, false if otherwise
        bool subtractColor(ColorClass &rhs);

        // Multiply the corresponding component color values by the adjustment
        // factor provided to adjust the brightness
        // input: a ColorClass
        // output: true if clipping is necessary, false if otherwise
        bool adjustBrightness(double adjFactor);

        // Print the component vaues to the console
        // input: N/A
        // output: N/A
        void printComponentValues();
};

// Row Column Class identifies a specific pixel within an image
class RowColumnClass
{
    private:
        int rowValue;
        int colValue;

    public:
        // Default ctor that sets both row and column values to -99999
        // input: N/A
        // output: N/A
        RowColumnClass();

        // Ctor that sets the row and column values to the corresponding values
        // input: row and column values
        // output: N/A
        RowColumnClass(int inRow, int inCol);

        // Set the appropriate row and col attributes
        // input: row and column
        // output: N/A
        void setRowCol(int inRow, int inCol);

        // Set the appropriate row attributes
        // input: row number
        // output: N/A
        void setRow(int inRow);

        // Set the appropriate col attributes
        // input: column number
        // output: N/A
        void setCol(int inCol);

        // Get the appropriate row attributes
        // input: N/A
        // output: row number
        int getRow();

        // Get the appropriate column attributes
        // input: N/A
        // output: column number
        int getCol();

        // Add the appropriate row column index of the input to the right
        // attributes of the class object
        // input: a RowColumnClass
        // output: column number
        void addRowColTo(RowColumnClass &intRowCol);

        // Print the row col attributes in the format of "[<row>, <col>]"
        // inout: N/A
        // output: N/A
        void printRowCol();
};


// Color image class defines a collection of color pixels in an array
class ColorImageClass
{
    private:
        ColorClass colorPixelArray [IMAGE_ROW_SIZE][IMAGE_COL_SIZE];

        // A private function to check if the row column are valid values
        // input: a RowColumnClass
        // output: return true if value, false otherwise
        bool checkRowCol(RowColumnClass &inRowCol);

    public:
        // Default constructor that sets all pixels in image to full black
        ColorImageClass();

        // Initilizes all image pixels to the color provided via input
        // inputs: a ColorClass
        // output: N/A
        void initializeTo(ColorClass &inColor);

        // Performs a pixel-wise addition (add the input image pixels to the
        // correspnding locations on the image)
        // inputs: a ColorImageClass
        // output: true if clipping needed; false otherwise
        bool addImageTo(ColorImageClass &rhsImg);

        // Set image value to the sum of the corresponding pixels in each image
        // of the imagesToAdd input parameter
        // input: number of the images added and the image array
        // output: true if clipping needed; false otherwise
        bool addImages(int numImgsAdd, ColorImageClass imagesToAdd []);

        // Set the pixel at the given row col location to the color specified
        // input: location of row and col and the ColorClass
        // output: true if clipping needed; false otherwise
        bool setColorAtLocation(RowColumnClass &inRowCol,
                                ColorClass &inColor);

        // Assign the outColor the color image pixel at the location specified
        // input: location of row and col and the ColorClass
        // output: true if the row col value are valid; false otherwise
        bool getColorAtLocation(RowColumnClass &inRowCol,
                                ColorClass &outColor);

        // Print the contents of the image to the screen
        // inout: N/A
        // output: N/A
        void printImage();
};



#ifdef ANDREW_TEST
#include "andrewTest.h"
#else



int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);

  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }

  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }

  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}



#endif



// ColorClass functions:

ColorClass::ColorClass()
{
    // The Default color is set to be white, meaning full value of all RGB
    redComp = ALLOWED_COLOR_MAXIMUM;
    greenComp = ALLOWED_COLOR_MAXIMUM;
    blueComp = ALLOWED_COLOR_MAXIMUM;
}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
    redComp = inRed;
    greenComp = inGreen;
    blueComp = inBlue;
    clipColorComps();
}

bool ColorClass::clipColorComps()
{
    int colorComps[NUMBER_OF_COLOR_COMPS] = {redComp, greenComp, blueComp};
    bool flagClipping = false;

    for (int colorIdx = 0; colorIdx < NUMBER_OF_COLOR_COMPS; colorIdx ++)
    {
        if (colorComps[colorIdx] > ALLOWED_COLOR_MAXIMUM)
        {
            colorComps[colorIdx] = ALLOWED_COLOR_MAXIMUM;
            flagClipping = true;
        }
        else if (colorComps[colorIdx] < ALLOWED_COLOR_MINIMUM)
        {
            colorComps[colorIdx] = ALLOWED_COLOR_MINIMUM;
            flagClipping = true;
        }
    }
    redComp = colorComps[RED_INDEX];
    greenComp = colorComps[GREEN_INDEX];
    blueComp = colorComps[BLUE_INDEX];

    return flagClipping;
}

void ColorClass::setToBlack()
{
    setTo(ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MINIMUM);
}

void ColorClass::setToRed()
{
    setTo(ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MINIMUM);
}

void ColorClass::setToGreen()
{
    setTo(ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MINIMUM);
}

void ColorClass::setToBlue()
{
    setTo(ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MAXIMUM);
}

void ColorClass::setToWhite()
{
    setTo(ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MAXIMUM);
}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
    redComp = inRed;
    greenComp = inGreen;
    blueComp = inBlue;
    return clipColorComps();
}

bool ColorClass::setTo(ColorClass &inColor)
{
    redComp = inColor.redComp;
    greenComp = inColor.greenComp;
    blueComp = inColor.blueComp;
    return clipColorComps();
}

bool ColorClass::addColor(ColorClass &rhs)
{
    redComp += rhs.redComp;
    greenComp += rhs.greenComp;
    blueComp += rhs.blueComp;
    return clipColorComps();
}

bool ColorClass::subtractColor(ColorClass &rhs)
{
    redComp -= rhs.redComp;
    greenComp -= rhs.greenComp;
    blueComp -= rhs.blueComp;
    return clipColorComps();
}

bool ColorClass::adjustBrightness(double adjFactor)
{
    redComp *= adjFactor;
    greenComp *= adjFactor;
    blueComp *= adjFactor;
    return clipColorComps();
}

void ColorClass::printComponentValues()
{
    cout << "R: " << redComp << " G: " << greenComp << " B: " << blueComp;
}



// RowColumnClass functions:

RowColumnClass::RowColumnClass()
{
    rowValue = DEFAULT_ROW_COL;
    colValue = DEFAULT_ROW_COL;
}

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    rowValue = inRow;
    colValue = inCol;
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    rowValue = inRow;
    colValue = inCol;
}

void RowColumnClass::setRow(int inRow)
{
    rowValue = inRow;
}

void RowColumnClass::setCol(int inCol)
{
    colValue = inCol;
}

int RowColumnClass::getRow()
{
    return rowValue;
}

int RowColumnClass::getCol()
{
    return colValue;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    rowValue += inRowCol.getRow();
    colValue += inRowCol.getCol();
}

void RowColumnClass::printRowCol()
{
    cout << "[" << rowValue << ", " << colValue << "]";
}



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
           inRowCol.getRow() > 0              &&
           inRowCol.getCol() < IMAGE_COL_SIZE &&
           inRowCol.getCol() > 0;
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
