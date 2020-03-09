#include <iostream>
using namespace std;

#include "RowColumnClass.h"
#include "constants.h"

// RowColumnClass functions:

RowColumnClass::RowColumnClass()
{
    rowValue = DEFAULT_ROW_COL;
    colValue = DEFAULT_ROW_COL;
}

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    rowValue = inRow;
    colValue = inCol;
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    rowValue = inRow;
    colValue = inCol;
}

void RowColumnClass::setRow(int inRow)
{
    rowValue = inRow;
}

void RowColumnClass::setCol(int inCol)
{
    colValue = inCol;
}

int RowColumnClass::getRow()
{
    return rowValue;
}

int RowColumnClass::getCol()
{
    return colValue;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    rowValue += inRowCol.getRow();
    colValue += inRowCol.getCol();
}

void RowColumnClass::printRowCol()
{
    cout << "[" << rowValue << ", " << colValue << "]";
}
