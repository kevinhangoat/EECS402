#include <iostream>
#include <cstdlib>
using namespace std;

#include "LinkedNodeClass.h"
#include "constants.h"



// Program Header
// Programmer: Yutian Han
// Date: April 2020
// Purpose: EECS Project5
// Functions for LinkedNodeClass (Scope resolution)



//The ONLY constructor for the linked node class - it takes in the
//newly created node's previous pointer, value, and next pointer,
//and assigns them.
// inputs: Address of node that comes before this one
//         Value to be contained in this node
//         Address of node that comes after this one
template <class T>
LinkedNodeClass< T >::LinkedNodeClass(LinkedNodeClass< T > *inPrev,
                                      const T &inVal,
                                      LinkedNodeClass< T > *inNext)
{
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}



template <class T>
T LinkedNodeClass< T >::getValue() const
{
    return nodeVal;
}



template <class T>
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
    return nextNode;
}



template <class T>
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
    return prevNode;
}



//Sets the object’s next node pointer to NULL.
template <class T>
void LinkedNodeClass< T >::setNextPointerToNull()
{
    nextNode = NULL;
}



//Sets the object's previous node pointer to NULL.
template <class T>
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
    prevNode = NULL;
}



//This function DOES NOT modify "this" node. Instead, it uses
//the pointers contained within this node to change the previous
//and next nodes so that they point to this node appropriately.
//In other words, if "this" node is set up such that its prevNode
//pointer points to a node (call it "A"), and "this" node's
//nextNode pointer points to a node (call it "B"), then calling
//setBeforeAndAfterPointers results in the node we're calling
//"A" to be updated so its "nextNode" points to "this" node, and
//the node we're calling "B" is updated so its "prevNode" points
//to "this" node, but "this" node itself remains unchanged.
template <class T>
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
    if (prevNode != NULL)
    {
        if (nextNode != NULL)
        {
            nextNode -> prevNode = this;
            prevNode -> nextNode = this;
        }
        else
        {
            prevNode -> nextNode = this;
        }
    }
    else
    {
        if (nextNode != NULL)
        {
            nextNode -> prevNode = this;
        }
    }
}
