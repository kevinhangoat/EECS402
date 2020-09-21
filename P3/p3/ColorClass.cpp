#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#include "ColorClass.h"
#include "constants.h"

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

void ColorClass::setToYellow()
{
    setTo(ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MINIMUM);
}

void ColorClass::setToMagenta()
{
    setTo(ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MAXIMUM);
}

void ColorClass::setToCyan()
{
    setTo(ALLOWED_COLOR_MINIMUM, ALLOWED_COLOR_MAXIMUM, ALLOWED_COLOR_MAXIMUM);
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


// Functions below are for image RGB readings


bool ColorClass::readValueRGB(ifstream &inFile)
{
    int colorComps[NUMBER_OF_COLOR_COMPS];

    bool validInputFound = false;
    for (int colorIdx = 0; colorIdx < NUMBER_OF_COLOR_COMPS; colorIdx ++)
    {
        validInputFound = false;
        while (!validInputFound)
        {
            if (inFile.eof())
            {
                cout << "Error: EOF when reading color" << endl;
                return validInputFound;
            }
            else if (inFile.fail())
            {
                inFile.clear();
                inFile.ignore(200, '\n');
                cout << "Error: Reading PPM color" << endl;
                return validInputFound;
            }
            else
            {
                validInputFound = true;
            }
        }
        inFile >> colorComps[colorIdx];
    }

    redComp = colorComps[RED_INDEX];
    greenComp = colorComps[GREEN_INDEX];
    blueComp = colorComps[BLUE_INDEX];
    return validInputFound;
}

bool ColorClass::writeValueRGB(ofstream &outFile)
{
    outFile << redComp << " " << greenComp << " " << blueComp << " ";
    return true;
}

bool ColorClass::encodePixel(const int encodingVal)
{
    // cout << encodingVal << endl;
    switch (encodingVal)
    {
        case ENCODING_VAL_ZERO:
            encodeRGB(EVEN, EVEN, EVEN);
            return true;
        case ENCODING_VAL_ONE:
            encodeRGB(ODD, EVEN, EVEN);
            return true;
        case ENCODING_VAL_TWO:
            encodeRGB(EVEN, ODD, EVEN);
            return true;
        case ENCODING_VAL_THREE:
            encodeRGB(EVEN, EVEN, ODD);
            return true;
        case ENCODING_VAL_FOUR:
            encodeRGB(ODD, ODD, ODD);
            return true;
        case ENCODING_VAL_FIVE:
            encodeRGB(ODD, ODD, EVEN);
            return true;
        case ENCODING_VAL_SIX:
            encodeRGB(ODD, EVEN, ODD);
            return true;
        case ENCODING_VAL_SEVEN:
            encodeRGB(ODD, ODD, ODD);
            return true;
        default:
            return false;
    }
}

void ColorClass::encodeRGB(bool isRedEven, int isGreenEven, int isBlueEven)
{
    if (isRedEven && redComp % 2 !=0)
    {
        redComp --;
    }
    else if (!isRedEven && redComp % 2 == 0)
    {
        redComp ++;
    }

    if (isGreenEven && greenComp % 2 !=0)
    {
        greenComp --;
    }
    else if (!isGreenEven && greenComp % 2 == 0)
    {
        greenComp ++;
    }

    if (isBlueEven && blueComp % 2 !=0)
    {
        blueComp --;
    }
    else if (!isBlueEven && blueComp % 2 == 0)
    {
        blueComp ++;
    }
}

void ColorClass::decodePixel()
{
    if (redComp % 2 == 0   && greenComp % 2 == 0 && blueComp % 2 == 0)
    {
        setToBlack();
    }
    else if (redComp % 2 != 0 && greenComp % 2 == 0 && blueComp % 2 ==0)
    {
        setToRed();
    }
    else if (redComp % 2 == 0 && greenComp % 2 != 0 && blueComp % 2 ==0)
    {
        setToGreen();
    }
    else if (redComp % 2 == 0 && greenComp % 2 == 0 && blueComp % 2 !=0)
    {
        setToBlue();
    }
    else if (redComp % 2 != 0 && greenComp % 2 != 0 && blueComp % 2 !=0)
    {
        setToWhite();
    }
    else if (redComp % 2 != 0 && greenComp % 2 != 0 && blueComp % 2 ==0)
    {
        setToYellow();
    }
    else if (redComp % 2 != 0 && greenComp % 2 == 0 && blueComp % 2 !=0)
    {
        setToMagenta();
    }
    else if (redComp % 2 == 0 && greenComp % 2 != 0 && blueComp % 2 !=0)
    {
        setToCyan();
    }
}
