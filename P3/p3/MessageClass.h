#ifndef MESSAGECLASS_H
#define MESSAGECLASS_H


// Color image class defines a collection of color pixels in an array
class MessageClass
{
    private:
        bool validFileFound;
        int messageRowSize;
        int messageColSize;
        int **messageMatrix;

    public:
        // Default constructor that sets all pixels in image to full black
        MessageClass();

        // Read a input PPM file and create a corresponding ColorImageClass
        // inout: N/A
        // output: N/A
        bool readMessageFile(const string &inFname);

        // Write a output PPM file and create a corresponding ColorImageClass
        // input: N/A
        // output: N/A
        bool writeMessageFile(const string &outFname);

        // get the message content matrix pointer
        // input: N/A
        // output: message content matrix
        int** getMessageMatrix();

        // get the message row size
        // input: N/A
        // output: message content matrix
        int getMessageRowSize();

        // get the message column size
        // input: N/A
        // output: message content matrix
        int getMessageColSize();
};

#endif
