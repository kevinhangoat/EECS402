#include "EventClass.h"

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
// The functions for the eventClass


EventClass::EventClass()
{
    eventType = NO_EVENT;
    value = NO_EVENT;
}


EventClass::EventClass(int type, const int &inVal)
{
    eventType = type;
    value = inVal;
}


int EventClass::getEventType()
{
    return eventType;
}


bool EventClass::operator<=(const EventClass &rhs)
{
    bool isSmaller = false;

    if (value <= rhs.value)
    {
        isSmaller = true;
    }

    return isSmaller;
}
