#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
#include "SimulatorClass.h"
#include "EventClass.h"
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "SortedListClass.h"
#include "constants.h"
#include "random.h"


// Program Header
// Programmer: Yutian Han
// Date: April 2020
// Purpose: EECS Project5
// The simulator class generate the whole simulation


SimulatorClass::SimulatorClass(ifstream &inStream,
                               int inCarSize, string inName)
{
    inStream >> closingTime >> riderArrivalMean >> riderArrivalStddev
             >> carArrivalMin >> carArrivalMax >> percentSFP >> percentFP
             >> idealNumSFP >> idealNumFP;

    //initialize variables
    int seed;
    cout << "Enter the seed: ";
    cin >> seed;
    numSeats = inCarSize;
    srand(seed);

    stdSize = INITIAL_COUNT;
    fpSize = INITIAL_COUNT;
    sfpSize = INITIAL_COUNT;

    stdTotal = INITIAL_COUNT;
    fpTotal = INITIAL_COUNT;
    sfpTotal = INITIAL_COUNT;

    stdMax = INITIAL_COUNT;
    fpMax = INITIAL_COUNT;
    sfpMax = INITIAL_COUNT;

    attractionName = inName;
    cout << "Welcome to " << attractionName << "!" << endl;
}



void SimulatorClass::handleNextEvent(int &riderT, int &carT)
{
    EventClass nextEvent;
    EventClass removedEvent;

    //Gets the first event in the sorted list
    eventList.getElemAtIndex(FIRST_EVENT_IDX, nextEvent);

    if (nextEvent.getEventType() == CAR_EVENT)
    {
        carArrival(carT);
        eventList.removeFront(removedEvent);
    }
    else
    {
        riderArrival(riderT);
        eventList.removeFront(removedEvent);
    }
}



int SimulatorClass::getEventSize()
{
    int length = eventList.getNumElems();
    return length;
}


int SimulatorClass::riderArrival(int &riderTime)
{
    int nextArrTime;
    double randVal = getUniform(MIN_PERCENT, MAX_PERCENT);

    //if rider has SFP
    if (randVal < percentSFP)
    {
        lineSFP.enqueue(riderTime);
        sfpSize ++;
        sfpTotal ++;
        cout << "One person joined the Super Fast Pass line at time"
             << "  " << riderTime << endl;
        printLineStats();
    }
    //if rider has FP
    else if ((randVal > percentSFP) && (randVal < percentSFP + percentFP))
    {
        lineFP.enqueue(riderTime);
        fpSize ++;
        fpTotal ++;
        cout << "One person joined the Fast Pass line at time"
             << "  " << riderTime << endl;
        printLineStats();
    }
    //if rider has std pass
    else
    {
        lineSTD.enqueue(riderTime);
        stdSize ++;
        stdTotal ++;
        cout << "One person joined the regular line at time"
             << "  " << riderTime << endl;
        printLineStats();
    }

    //update the maximum line size for statistics
    if (stdSize > stdMax)
    {
        stdMax = stdSize;
    }

    if (fpSize > fpMax)
    {
        fpMax = fpSize;
    }

    if (sfpSize > sfpMax)
    {
        sfpMax = sfpSize;
    }

    //generate the next rider
    nextArrTime = riderTime + getNormal(riderArrivalMean, riderArrivalStddev);
    cout << "next rider arrival time is: " << nextArrTime << endl;

    if (nextArrTime > closingTime)
    {
        cout << "Attraction is closing. This passenger can't enter." << endl;
        return riderTime;
    }
    else
    {
        EventClass riderArrival (PASSENGER_EVENT, nextArrTime);
        eventList.insertValue(riderArrival);
        riderTime = nextArrTime;
    }
    return nextArrTime;
}



int SimulatorClass::carArrival(int &carTime)
{
    bool carIsFilled = false;
    int spaceLeft = numSeats;

    int idealNumSTD = numSeats - idealNumSFP - idealNumFP;
    int nextArrTime;

    int riderToBoard;
    int numLoadedFromSTDLine = INITIAL_COUNT;
    int numLoadedFromFPLine = INITIAL_COUNT;
    int numLoadedFromSFPLine = INITIAL_COUNT;

    if (noRiderWaiting())
    {
        cout << "Nobody is waiting. Simulation ends" << endl;
        return 0;
    }
    else if (carTime > closingTime)
    {
        cout << "We are closing! But people in the line can still play"
             << endl;
    }

    cout << "A car just arrived at time " << carTime
         << ", starting to board riders." << endl;
    // dequeue from each line
    int idxSFP;
    for (idxSFP = 0; idxSFP < idealNumSFP; idxSFP++)
    {
        if (lineSFP.dequeue(riderToBoard) && !carIsFilled)
        {
            cout <<
            spaceLeft--;
            sfpSize--;
            numLoadedFromSFPLine ++;
            sfpTotalWaitTime += (carTime - riderToBoard);
            carIsFilled = checkNumSeats(spaceLeft);
        }
    }

    int idxFP;
    for (idxFP = 0; idxFP < idealNumFP; idxFP++)
    {
        if (lineFP.dequeue(riderToBoard) && !carIsFilled)
        {
            spaceLeft--;
            fpSize--;
            numLoadedFromFPLine ++;
            fpTotalWaitTime += (carTime - riderToBoard);
            carIsFilled = checkNumSeats(spaceLeft);
        }
    }

    int idxSTD;
    for (idxSTD = 0; idxSTD < idealNumSTD; idxSTD++)
    {
        if (lineSTD.dequeue(riderToBoard) && !carIsFilled)
        {
            spaceLeft--;
            stdSize--;
            numLoadedFromSTDLine ++;
            stdTotalWaitTime += (carTime - riderToBoard);
            carIsFilled = checkNumSeats(spaceLeft);
        }
    }

    carIsFilled = checkNumSeats(spaceLeft);

    // Further dequeue if car is not filled, from SFP to FP to STD
    while (lineSFP.dequeue(riderToBoard) && !carIsFilled)
    {
        spaceLeft--;
        numLoadedFromSFPLine ++;
        sfpSize--;
        sfpTotalWaitTime += (carTime - riderToBoard);
        carIsFilled = checkNumSeats(spaceLeft);
    }

    while (lineFP.dequeue(riderToBoard) && !carIsFilled)
    {
        spaceLeft--;
        numLoadedFromFPLine ++;
        fpSize--;
        fpTotalWaitTime += (carTime - riderToBoard);
        carIsFilled = checkNumSeats(spaceLeft);
    }

    while (lineSTD.dequeue(riderToBoard) && !carIsFilled)
    {
        spaceLeft--;
        numLoadedFromSTDLine ++;
        stdSize--;
        stdTotalWaitTime += (carTime - riderToBoard);
        carIsFilled = checkNumSeats(spaceLeft);
    }

    cout << "Riders in this ride are composed of:" << endl;
    cout << "Standard Line:" << "  " << numLoadedFromSTDLine << endl;
    cout << "FP Line:" << "        " << numLoadedFromFPLine << endl;
    cout << "SFP Line:" << "       " << numLoadedFromSFPLine << endl;
    cout << "Space Left:" << "     " << spaceLeft << endl;


    nextArrTime = carTime + getUniform(carArrivalMin, carArrivalMax);

    cout << "next car arrival time is: " << nextArrTime << endl;
    EventClass carEvent(CAR_EVENT, nextArrTime);
    eventList.insertValue(carEvent);

    carTime = nextArrTime;
    return nextArrTime;
}


bool SimulatorClass::noRiderWaiting()
{
    int numRidersWaiting = lineSTD.getNumElems() +
                           lineSFP.getNumElems() +
                           lineFP.getNumElems();
    if( numRidersWaiting == 0 )
    {
        return true;
    }
    return false;

}

bool SimulatorClass::checkNumSeats(int spaceLeft)
{
    bool carIsFilled = false;
    if (spaceLeft == EMPTY_LIST_SIZE)
    {
        carIsFilled = true;
    }
    return carIsFilled;
}


void SimulatorClass::performStatistics()
{
    cout << endl << endl << endl;
    cout << "Statistics Begin:" << endl;

    //get the avgWaitTime
    stdAvgWaitTime = stdTotalWaitTime / stdTotal;
    fpAvgWaitTime = fpTotalWaitTime / fpTotal;
    sfpAvgWaitTime = sfpTotalWaitTime / sfpTotal;

    cout << "Total number of people in each line:" << endl;
    cout << "Standard Line:" << "  " << stdTotal << endl;
    cout << "FP Line:" << "        " << fpTotal << endl;
    cout << "SFP Line:" << "       " << sfpTotal << endl << endl;

    cout << "Average Waiting Time at each line:" << endl;
    cout << "Standard Line:" << "  " << stdAvgWaitTime << endl;
    cout << "FP Line:" << "        " << fpAvgWaitTime << endl;
    cout << "SFP Line:" << "       " << sfpAvgWaitTime << endl << endl;

    cout << "Maximum length of each line:" << endl;
    cout << "Standard Line:" << "  " << stdMax << endl;
    cout << "FP Line:" << "        " << fpMax << endl;
    cout << "SFP Line:" << "       " << sfpMax << endl << endl;
}



void SimulatorClass::printLineStats()
{
    cout << "Number of People in each line:" << endl;
    cout << "Standard Line:" << "  " << stdSize << endl;
    cout << "FP Line:" << "        " << fpSize << endl;
    cout << "SFP Line:" << "       " << sfpSize << endl;
}


SimulatorClass::~SimulatorClass()
{
    eventList.clear();
    int removed;

    for (int i = 0; i < lineSTD.getNumElems(); i++)
    {
        lineSTD.dequeue(removed);
    }

    for (int i = 0; i < lineFP.getNumElems(); i++)
    {
        lineFP.dequeue(removed);
    }

    for (int i = 0; i < lineSFP.getNumElems(); i++)
    {
        lineSFP.dequeue(removed);
    }
}
