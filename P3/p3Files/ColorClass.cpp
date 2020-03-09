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

    for (int colorIdx = 0; colorIdx < NUMBER_OF_COLOR_COMPS; colorIdx ++)
    {
        inFile >> colorComps[colorIdx];
    }

    redComp = colorComps[RED_INDEX];
    greenComp = colorComps[GREEN_INDEX];
    blueComp = colorComps[BLUE_INDEX];

    cout << redComp << endl;
    return !inFile.fail();
}
