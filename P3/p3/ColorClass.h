#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include "constants.h"

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

        // Set the color to yellow
        // input: N/A
        // output: N/A
        void setToYellow();

        // Set the color to Magenta
        // input: N/A
        // output: N/A
        void setToMagenta();

        // Set the color to Magenta
        // input: N/A
        // output: N/A
        void setToCyan();

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



        // functions below are for project 3

        // read RGB values from the infile
        // input: infile
        // output: a boolean showing if in file valid
        bool readValueRGB(ifstream &inFile);

        // write RGB values from the infile
        // input: infile
        // output: a boolean showing if in file valid
        bool writeValueRGB(ofstream &outFile);

        // encode the the message into each pixel
        // input: encoding value
        // output: N/A
        bool encodePixel(const int encodingVal);

        // encode the RGB by increasing or decreasing RGB by 1
        // input: encoding RGB
        // output: N/A
        void encodeRGB(bool isRedEven, int isGreenEven, int isBlueEven);

        // decode the RGB to the description color
        // input: N/A
        // output: N/A
        void decodePixel();
};

#endif
