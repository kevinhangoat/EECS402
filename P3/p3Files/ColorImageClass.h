#ifndef COLORIMAGECLASS_H
#define COLORIMAGECLASS_H


// Color image class defines a collection of color pixels in an array
class ColorImageClass
{
    private:
        int imageRowSize;
        int imageColSize;
        ColorClass **colorPixelArray;

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

        // Read a input PPM file and create a corresponding ColorImageClass
        // inout: N/A
        // output: N/A
        bool readPpmPixels(const string &inFname);
};

#endif
