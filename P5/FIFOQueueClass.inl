#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "constants.h"



// Program Header
// Programmer: Yutian Han
// Date: April 2020
// Purpose: EECS Project5
// Member functions for FIFOQueueClass (Scope resolution)



//Default Constructor. Will properly initialize a queue to
//be an empty queue, to which values can be added.
template <class T>
FIFOQueueClass< T >::FIFOQueueClass()
{
    head = NULL;
    tail = NULL;
}

//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
template <class T>
FIFOQueueClass< T >::~FIFOQueueClass()
{
    clear();
}

//Inserts the value provided (newItem) into the queue.
template <class T>
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
    LinkedNodeClass< T >* toInsertPtr;
    if (getNumElems() == 0)
    {
        toInsertPtr = new LinkedNodeClass< T >(NULL, newItem, NULL);
        head = toInsertPtr;
        tail = toInsertPtr;
    }
    else
    {
        toInsertPtr = new LinkedNodeClass< T >(tail, newItem, NULL);
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
template <class T>
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
    if (getNumElems() == 0) {
        return false;
    }
    else
    {
        outItem = head -> getValue();
        if (head -> getNext() == NULL)
        {
            head = NULL;
            tail = NULL;
            return true;
        }
        else
        {
            head = head -> getNext();
            delete head -> getPrev();
            head -> setPreviousPointerToNull();
            return true;
        }
    }
}

//Prints out the contents of the queue. All printing is done
//on one line, using a single space to separate values, and a
//single newline character is printed at the end.
template <class T>
void FIFOQueueClass< T >::print() const
{
    LinkedNodeClass< T >* curPtr = head;
    while (curPtr != NULL)
    {
        cout << curPtr -> getValue() << " ";
        curPtr = curPtr -> getNext();
    }
    cout << endl;
}

//Returns the number of nodes contained in the queue.
template <class T>
int FIFOQueueClass< T >::getNumElems() const
{
    LinkedNodeClass< T >* curPtr = head;
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
template <class T>
void FIFOQueueClass< T >::clear()
{
    LinkedNodeClass< T >* curPtr = head;
    LinkedNodeClass< T >* toDeletePtr = head;

    if (curPtr == NULL)
    {
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
