#ifndef _EVENT_CLASS_H_
#define _EVENT_CLASS_H_

#include <fstream>
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
// The event class generate an event for the simulation



class EventClass
{
    private:
        //type of event, includes car arrival and rider arrival
        int eventType;

        //value is the time
        int value;

    public:
        //default ctor to generate an empty event
        EventClass();

        //set the event type and time value to the given ones
        EventClass(int type, const int &inVal);

        //compare the value with another integer
        bool operator<=(const EventClass &rhs);

        //get the type of the event
        int getEventType();
};

#endif
