#ifndef _SIMULATION_CLASS_
#define _SIMULATION_CLASS_

#include <fstream>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "SortedListClass.h"
#include "EventClass.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include <string>
using namespace std;



// Program Header
// Programmer: Yutian Han
// Date: April 2020
// Purpose: EECS Project5
// The simulator class generate the whole simulation



class SimulatorClass
{
    private:
        //line for standard rider
        FIFOQueueClass < int > lineSTD;

        //line for fast pass rider
        FIFOQueueClass < int > lineFP;

        //line for super fast pass rider
        FIFOQueueClass < int > lineSFP;

        //list of events(arrivals of passengers and car)
        SortedListClass < EventClass > eventList;

        //variables from the simParams file
        int closingTime, carArrivalMin, carArrivalMax, idealNumSFP, idealNumFP;
        double riderArrivalMean, riderArrivalStddev, percentSFP, percentFP;

        //specs for the ride
        int stdSize, fpSize, sfpSize, numSeats;

        //statitics specs
        int stdTotal, fpTotal, sfpTotal;
        int stdMax, fpMax, sfpMax;
        int stdTotalWaitTime, fpTotalWaitTime, sfpTotalWaitTime;
        int stdAvgWaitTime, fpAvgWaitTime, sfpAvgWaitTime;


        //name of the simulator
        string attractionName;

    public:
        //ctor to generate simulator
        //input the infilestream, cart size, parkName
        SimulatorClass(ifstream &inStream, int inCarSize, string inName);

        //simulate the situation when the car arrives, including load riders
        //from different lines and estimate the next arrival of the car
        //input: current car event's time
        //output: next car's time
        int carArrival(int &carTime);

        //simulate the situation when the rider arrives, including put rider
        //into different lines and generate the next rider
        //input: current rider event's arrival time
        //output: next rider's time
        int riderArrival(int &riderTime);

        //calculate and print stats such as the averge waiting time and so on
        void performStatistics();

        //print how many people are waiting at each line
        void printLineStats();

        //takes in the current time of the rider's arrival the car's
        //arrival and manipulate at each condition
        void handleNextEvent(int &riderT, int &carT);

        //calculate and return the size of the event list
        int getEventSize();

        //check if tere are still seet left
        //input: number of seats left
        //output: true if no seat left
        bool checkNumSeats(int spaceLeft);

        //check if there are still ppl waiting
        //output true if there's none
        bool noRiderWaiting();

        //dtor for the simulator
        ~SimulatorClass();

};


#endif
