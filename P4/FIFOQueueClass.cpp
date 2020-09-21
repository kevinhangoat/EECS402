#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "constants.h"



// Program Header
// Programmer: Yutian Han
// Date: March 2020
// Purpose: EECS Project4
// Member functions for FIFOQueueClass (Scope resolution)



//Default Constructor. Will properly initialize a queue to
//be an empty queue, to which values can be added.
FIFOQueueClass::FIFOQueueClass()
{
    head = NULL;
    tail = NULL;
}

//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
FIFOQueueClass::~FIFOQueueClass()
{
    clear();
}

//Inserts the value provided (newItem) into the queue.
void FIFOQueueClass::enqueue(const int &newItem)
{
    LinkedNodeClass* toInsertPtr;
    if (getNumElems() == 0)
    {
        toInsertPtr = new LinkedNodeClass(NULL, newItem, NULL);
        head = toInsertPtr;
        tail = toInsertPtr;
    }
    else
    {
        toInsertPtr = new LinkedNodeClass(tail, newItem, NULL);
        toInsertPtr -> setBeforeAndAfterPointers();
        tail = toInsertPtr;
    }
}

//Attempts to take the next item out of the queue. If the
//queue is empty, the function returns false and the state
//of the reference parameter (outItem) is undefined. If the
//queue is not empty, the function returns true and outItem
//becomes a copy of the next item in the queue, which is
//removed from the data structure.
bool FIFOQueueClass::dequeue(int &outItem)
{
    if (getNumElems() == 0) {
        return false;
    }
    else
    {
        outItem = head -> getValue();
        head = head -> getNext();
        delete head -> getPrev();
        head -> setPreviousPointerToNull();
        return true;
    }
}

//Prints out the contents of the queue. All printing is done
//on one line, using a single space to separate values, and a
//single newline character is printed at the end.
void FIFOQueueClass::print() const
{
    LinkedNodeClass* curPtr = head;
    while (curPtr != NULL)
    {
        cout << curPtr -> getValue() << " ";
        curPtr = curPtr -> getNext();
    }
    cout << endl;
}

//Returns the number of nodes contained in the queue.
int FIFOQueueClass::getNumElems() const
{
    LinkedNodeClass* curPtr = head;
    int count = INITIAL_COUNT;

    while(curPtr != NULL)
    {
        count ++;
        curPtr= curPtr -> getNext();
    }
    return count;
}

//Clears the queue to an empty state without resulting in any
//memory leaks.
void FIFOQueueClass::clear()
{
    LinkedNodeClass* curPtr = head;
    LinkedNodeClass* toDeletePtr = head;

    if (curPtr == NULL)
    {
        cout << "The list is already empty" << endl;
    }
    else
    {
        while (curPtr != NULL)
        {
            curPtr = curPtr -> getNext();
            delete toDeletePtr;
            toDeletePtr = curPtr;
        }
    }
    head = NULL;
    tail = NULL;
}
