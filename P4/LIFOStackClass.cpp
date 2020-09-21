#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "LIFOStackClass.h"
#include "constants.h"



// Program Header
// Programmer: Yutian Han
// Date: March 2020
// Purpose: EECS Project4
// Member functions for LIFOQueueClass (Scope resolution)



//Default Constructor. Will properly initialize a stack to
//be an empty stack, to which values can be added.
LIFOStackClass::LIFOStackClass()
{
    head = NULL;
    tail = NULL;
}



//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
LIFOStackClass::~LIFOStackClass()
{
    clear();
}



//Inserts the value provided (newItem) into the stack.
void LIFOStackClass::push(const int &newItem)
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



//Attempts to take the next item out of the stack. If the
//stack is empty, the function returns false and the state
//of the reference parameter (outItem) is undefined. If the
//stack is not empty, the function returns true and outItem
//becomes a copy of the next item in the stack, which is
//removed from the data structure.
bool LIFOStackClass::pop(int &outItem)
{
    if (getNumElems() == 0) {
        return false;
    }
    else {
        outItem = tail -> getValue();
        tail = tail-> getPrev();
        delete tail -> getNext();
        tail -> setNextPointerToNull();
        return true;
    }
}



//Prints out the contents of the stack. All printing is done
//on one line, using a single space to separate values, and a
//single newline character is printed at the end.
void LIFOStackClass::print() const
{
    LinkedNodeClass* curPtr = head;
    while (curPtr != NULL)
    {
        cout << curPtr -> getValue() << " ";
        curPtr = curPtr -> getNext();
    }
    cout << endl;
}



//Returns the number of nodes contained in the stack.
int LIFOStackClass::getNumElems() const
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



//Clears the stack to an empty state without resulting in any
//memory leaks.
void LIFOStackClass::clear()
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
