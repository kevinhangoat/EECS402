#ifndef COLORIMAGECLASS_H
#define COLORIMAGECLASS_H
#include "MessageClass.h"


// Color image class defines a collection of color pixels in an array
class ColorImageClass
{
    private:
        bool validFileFound;
        string magicNum;
        int imageRowSize;
        int imageColSize;
        int maxVal;
        ColorClass **colorPixelArray;

        // A private function to check if the row column are valid values
        // input: a RowColumnClass
        // output: return true if value, false otherwise
        bool checkRowCol(RowColumnClass &inRowCol);



    public:
        // Default constructor that sets all pixels in image to full black
        ColorImageClass();

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
                                int &imageRowSize, int &imageColSize);

        // A private function read the maximum value of the PPM
        // input: input file stream, a boolean showing if the input
        //        file is valid and the maximum value
        // output: a boolean showing if the input file is valid
        bool readPpmMaxVal(ifstream &inFile, bool &validFileFound, int &maxVal);

        // A private function read a row
        // input: input file stream, a boolean showing if the input
        //        file is valid and the maximum value
        // output: a boolean showing if the input file is valid
        bool readPpmPixels(ifstream &inFile, bool &validFileFound,
                           const int imageRowSize, const int imageColSize);

        // Read a input PPM file and create a corresponding ColorImageClass
        // inout: N/A
        // output: N/A
        bool readPpmFile(const string &inFname);


        // Write a output PPM file and create a corresponding ColorImageClass
        // inout: N/A
        // output: N/A
        bool writePpmPixels(ofstream &outFile,
                            const int imageRowSize,
                            const int imageColSize);

        // Write a output PPM file and create a corresponding ColorImageClass
        // inout: N/A
        // output: N/A
        bool writePpmFile(const string &outFname);

        // Decode the message int a PPM file
        // inout: N/A
        // output: N/A
        void decodePpmFile();

        // Encode the message int a PPM file
        // inout: N/A
        // output: N/A
        bool encodePpmFile(RowColumnClass upperLeftLocation,
                           MessageClass &encodingMessage);
};

#endif
