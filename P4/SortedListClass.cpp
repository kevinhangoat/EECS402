#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "constants.h"



// Program Header
// Programmer: Yutian Han
// Date: March 2020
// Purpose: EECS Project4
// Functions for SortedListClass (Scope resolution)



SortedListClass::SortedListClass()
{
    head = NULL;
    tail = NULL;
}



//Copy constructor. Will make a complete (deep) copy of the list, such
//that one can be changed without affecting the other.
SortedListClass::SortedListClass(const SortedListClass &rhs)
{
    head = NULL;
    tail = NULL;
    for (int idx = 0; idx < rhs.getNumElems(); idx ++)
    {
        int curVal;
        rhs.getElemAtIndex(idx, curVal);
        insertValue(curVal);
    }
}



//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
SortedListClass::~SortedListClass()
{
    clear();
}



//Clears the list to an empty state without resulting in any
//memory leaks.
void SortedListClass::clear()
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

//Allows the user to insert a value into the list. Since this
//is a sorted list, there is no need to specify where in the list
//to insert the element. It will insert it in the appropriate
//location based on the value being inserted. If the node value
//being inserted is found to be "equal to" one or more node values
//already in the list, the newly inserted node will be placed AFTER
//the previously inserted nodes.
void SortedListClass::insertValue(const int &valToInsert)
{
    if (head == NULL)
    {
        LinkedNodeClass* insertPtr;
        insertPtr = new LinkedNodeClass(NULL, valToInsert, NULL);
        head = insertPtr;
        tail = insertPtr;
    }
    else
    {
        LinkedNodeClass* curPtr = head;
        int curVal = head -> getValue();

        while ((valToInsert >= curVal) && (curPtr != NULL))
        {
            if (curPtr -> getNext() != NULL)
            {
                curPtr = curPtr -> getNext();
                curVal = curPtr -> getValue();
            }
            else
            {
                curPtr = NULL;
            }
        }

        if (curPtr == head)
        {
            LinkedNodeClass* insertPtr;
            insertPtr = new LinkedNodeClass(NULL, valToInsert, head);
            insertPtr -> setBeforeAndAfterPointers();
            head = insertPtr;
        }
        else if (curPtr == NULL) {
            LinkedNodeClass* insertPtr;
            insertPtr = new LinkedNodeClass(tail, valToInsert, NULL);
            insertPtr-> setBeforeAndAfterPointers();
            tail = insertPtr;
        }
        else {
            LinkedNodeClass* insertPtr;
            insertPtr = new LinkedNodeClass(curPtr->getPrev(),
                            valToInsert, curPtr);
            insertPtr-> setBeforeAndAfterPointers();
        }
    }
}

//Prints the contents of the list from head to tail to the screen.
//Begins with a line reading "Forward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
void SortedListClass::printForward() const
{
    cout << "Forward List Contents Follow:" << endl;
    LinkedNodeClass* forwardPtr = head;
    while (forwardPtr != NULL)
    {
        cout << "  " << forwardPtr -> getValue() << endl;
        forwardPtr = forwardPtr -> getNext();
    }
    cout << "End Of List Contents" << endl;
}

//Prints the contents of the list from tail to head to the screen.
//Begins with a line reading "Backward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
void SortedListClass::printBackward() const
{
    cout << "Backward List Contents Follow:" << endl;
    LinkedNodeClass* backwardPtr = tail;
    while (backwardPtr != NULL)
    {
        cout << "  " << backwardPtr -> getValue() << endl;
        backwardPtr = backwardPtr -> getPrev();
    }
    cout << "End Of List Contents" << endl;
}

//Removes the front item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the first item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
bool SortedListClass::removeFront(int &theVal)
{
    if (getNumElems() == 0)
    {
        return false;
    }
    else
    {
        theVal = head -> getValue();
        head = head -> getNext();
        delete head -> getPrev();
        head -> setPreviousPointerToNull();
        return true;
    }
}

//Removes the last item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the last item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
bool SortedListClass::removeLast(int &theVal)
{
    if (getNumElems() == 0)
    {
        return false;
    }
    else
    {
        theVal = tail -> getValue();
        tail = tail -> getPrev();
        delete tail -> getNext();
        tail -> setNextPointerToNull();
        return true;
    }
}

//Returns the number of nodes contained in the list.
int SortedListClass::getNumElems() const
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

//Provides the value stored in the node at index provided in the
//0-based "index" parameter. If the index is out of range, then outVal
//remains unchanged and false is returned. Otherwise, the function
//returns true, and the reference parameter outVal will contain
//a copy of the value at that location.
bool SortedListClass::getElemAtIndex(const int index, int &outVal) const
{
    if (index >= getNumElems())
    {
        return false;
    }
    else if (index < 0)
    {
        cout << "Index is smaller than zero" << endl;
        return false;
    }
    else
    {
        LinkedNodeClass* curPtr = head;
        int curIndex = FIRST_IDX;

        while(curIndex != index)
        {
            curPtr= curPtr -> getNext();
            curIndex ++;
        }
        outVal = curPtr -> getValue();
        return true;
    }
}
