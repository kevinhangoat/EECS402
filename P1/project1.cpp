#include <iostream>
using namespace std;



// Program Header
// Programmer: Yutian Han
// Date: January 2020
// Purpose: EECS Project1; Fit triangles to Approximate the area
//          between the curve and the x-axis.



const char APPROXIMATE_RECTS_OPTION = '1';
const char EXPERIMENT_PRECISION_OPTION = '2';
const char QUIT_PROGRAM_OPTION = '3';
const int SQUARED_POWER = 2;
const int CUBED_POWER = 3;
const double LARGE_NUMBER = 100000000.0;



//RESUBMISSION CODE UPDATE
// print the bsaic menu on the terminal
// no input and output
void printMenu();
// calculate the powers of the input number
// input the number and the power, output the number to the power
double toThePower(double val, int power);
// calclate y (the height of the rectangular) at a certain x value
// input a, b, c and d coefficients of the polynomial, the xvalue and the
// result value (as reference, which is updated in the the function).
// output a bool that shows if the result is positive
bool evaluateCubicFormula(double aCoeff, double bCoeff, double cCoeff,
                          double dCoeff, double xValue, double &resultVal);
// approximate the area under a curve (3rd order polynomial) by seperating
// the area into rectangulars
// input a, b, c, d coefficients of the polynomial, the start and end x value
// and the number of rectangulars.
// output the approximated area
double approximateAreaWithRect(double aCoeff, double bCoeff, double cCoeff,
                               double dCoeff, double startX, double endX,
                               int numRects);



#ifdef ANDREW_TEST
#include "andrewTest.h"
#else



int main()
{
    bool actionQuit = false;

    while (!actionQuit)
    {
        // print initial menu and get user choice
        printMenu();
        cout << "YOUR CHOICE: ";
        char userChoice;
        cin >> userChoice;

        if (userChoice == QUIT_PROGRAM_OPTION)
        {
            actionQuit = true;
            cout << "Thanks for using this program" << endl;
        }
        else if (userChoice == APPROXIMATE_RECTS_OPTION)
        {
            cout <<
            "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
            double aCoeff;
            double bCoeff;
            double cCoeff;
            double dCoeff;
            cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;

            cout << "Now enter x start and end values: ";
            double startX;
            double endX;
            cin >> startX >> endX;

            //RESUBMISSION CODE UPDATE
            // in case of bad input: startx > endx
            while (startX > endX)
            {
                cout << "x start must be smaller than x end! Retry!" << endl;
                cout << "Now enter x start and end values: ";
                cin >> startX >> endX;
            }

            cout << "Enter the number of rectangles to use: ";
            int numRects;
            cin >> numRects;

            //RESUBMISSION CODE UPDATE
            // in case of bad input: negative number of rects
            while (numRects < 0)
            {
                cout
                << "Number of rectangles need to be a positive integer. Retry!"
                << endl;
                cout << "Enter the number of rectangles to use: ";
                cin >> numRects;
            }

            double area;
            area =
            approximateAreaWithRect(aCoeff, bCoeff, cCoeff, dCoeff,
                                    startX, endX, numRects);
            cout << "Rectangle result is: " << area << endl;
        }
        else if (userChoice == EXPERIMENT_PRECISION_OPTION)
        {
            cout <<
            "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
            double aCoeff;
            double bCoeff;
            double cCoeff;
            double dCoeff;
            cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;

            cout << "Now enter x start and end values: ";
            double startX;
            double endX;
            cin >> startX >> endX;

            //RESUBMISSION CODE UPDATE
            // in case bad input: startx > endx
            while (startX > endX)
            {
                cout << "x start must be smaller than x end! Retry!" << endl;
                cout << "Now enter x start and end values: ";
                cin >> startX >> endX;
            }

            cout << "Enter correct answer: ";
            double correctAreaAnswer;
            cin >> correctAreaAnswer;

            cout << "Enter precision to reach: ";
            double precision;
            cin >> precision;

            //RESUBMISSION CODE UPDATE
            while (precision < 0)
            {
                cout << "Precision should be positive! Retry!" << endl;
                cout << "Enter precision to reach: ";
                cin >> precision;
            }

            // start to test numRects at 0
            int numRects;
            numRects = 0;
            // set initial error to be a big number;
            double error = LARGE_NUMBER;

            while (error > precision && numRects < 100)
            {
                numRects ++;

                double estimatedAreaAnswer =
                approximateAreaWithRect(aCoeff, bCoeff, cCoeff, dCoeff,
                                          startX, endX, numRects);

                error = estimatedAreaAnswer - correctAreaAnswer;

                // take the absolute value of error
                if (error < 0)
                {
                    error *= -1;
                }
            }

            if (numRects == 100)
            {
                cout << "Tried 100 rectangles without reaching precision"
                     << endl;
            }
            else
            {
                cout << "Rectangles needed to reach precision: "
                     << numRects << endl;
            }
        }
        else
        {
            // in case of bad input: choices other than 1 2 3
            cout << "You may only enter 1, 2 or 3 for choices" << endl;
        }
    }
    return 0;
}



#endif



//RESUBMISSION CODE UPDATE
void printMenu()
{
    cout << APPROXIMATE_RECTS_OPTION
         << ". Approximate Integral Using Rectangles" << endl;
    cout << EXPERIMENT_PRECISION_OPTION
         << ". Experiment With Rectangle Precision" << endl;
    cout << QUIT_PROGRAM_OPTION << ". Quit The Program" << endl;
}



double toThePower(double val, int power){
    double result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= val;
    }
    return result;
}



bool evaluateCubicFormula(double aCoeff, double bCoeff, double cCoeff,
double dCoeff, double xValue, double &resultVal)
{
    double y = aCoeff * toThePower(xValue, CUBED_POWER)
             + bCoeff * toThePower(xValue, SQUARED_POWER)
             + cCoeff * xValue + dCoeff;
    resultVal = y;
    if (y >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



double approximateAreaWithRect(double aCoeff, double bCoeff, double
cCoeff, double dCoeff, double startX, double endX, int numRects)
{
    double widthRect = (endX - startX) / numRects;
    double xValue = startX - widthRect / 2;
    double area = 0;
    for (int i = 0; i < numRects; i++)
    {
        xValue += widthRect;
        double heightRect;
        bool yIsPositive = evaluateCubicFormula(aCoeff, bCoeff, cCoeff,
                                                dCoeff, xValue, heightRect);
        if (yIsPositive)
        {
            area += widthRect * heightRect;
        }
        else
        {
            area -= widthRect * heightRect;
        }
    }
    return area;
}
