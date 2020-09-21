#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "constants.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "MessageClass.h"
#include "printMenu.h"
#include "overcomeFailState.h"



// Program Header
// Programmer: Yutian Han
// Date: March 2020
// Purpose: EECS Project3



#ifdef ANDREW_TEST
#include "andrewTest.h"
#else



int main(int argc, char *argv[])
{
    // error checking for number of input files
    if (argc != RIGHT_NUMBER_OF_INPUT)
    {
        cout << "Usage: ./project3.exe <startPPM.ppm>" << endl;
        exit(EXIT_WRONG_NUMBER_OF_INPUT);
    }



    // Read ppm file
    cout <<  "Reading initial image from: " << argv[IDX_FILE_ONE] << endl;
    string inFileName = argv[IDX_FILE_ONE];
    ColorImageClass image;



    //error checking for image reading
    if (image.readPpmFile(inFileName))
    {
        cout << "Image read successful: Yes" << endl;
    }
    else
    {
        cout << "Image read successful: No" << endl;
        cout << "Error: While reading the image, an error was encountered. "
             << "Exiting the program!" << endl;
        exit(EXIT_UNABLE_TO_READ_PPM);
    }



    int userChoice;
    while (userChoice != EXIT_OPTION)
    {
        printMenu();
        userChoice = overcomeFailState(userChoice);


        if (userChoice == ENCODE_OPTION)
        {
            cout << "Enter name of file containing message: ";

            string msgFileName;
            cin >> msgFileName;

            cout << "Enter row and column for message placement: ";
            int inRow;
            int inCol;
            inRow = overcomeFailState(inRow);
            inCol = overcomeFailState(inCol);
            RowColumnClass upperLeftLocation(inRow, inCol);
            MessageClass message;

            if (message.readMessageFile(msgFileName))
            {
                if (!image.encodePpmFile(upperLeftLocation, message))
                {
                    cout << "Message encode successful: No" << endl;
                }
                else
                {
                    cout << "Message encode successful: Yes" << endl;
                }
            }
            else
            {
                cout << "Message encode successful: No" << endl;
            }
        }


        else if (userChoice == DECODE_OPTION)
        {
            image.decodePpmFile();
        }


        else if (userChoice == WRITE_OPTION)
        {
            string outFileName;
            cout << "Enter name of file to write image to: ";
            cin >> outFileName;
            if(image.writePpmFile(outFileName))
            {
                cout << "Image write successful: Yes" << endl;
            };
        }


        else if (userChoice == EXIT_OPTION)
        {
            cout << "Thanks for using this program!" << endl;
        }


        else
        {
            cout << "You may only enter the option that is provided" << endl;
        }
    }
    return 0;
}



#endif
