#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

// Row Column Class identifies a specific pixel within an image
class RowColumnClass
{
    private:
        int rowValue;
        int colValue;

    public:
        // Default ctor that sets both row and column values to -99999
        // input: N/A
        // output: N/A
        RowColumnClass();

        // Ctor that sets the row and column values to the corresponding values
        // input: row and column values
        // output: N/A
        RowColumnClass(int inRow, int inCol);

        // Set the appropriate row and col attributes
        // input: row and column
        // output: N/A
        void setRowCol(int inRow, int inCol);

        // Set the appropriate row attributes
        // input: row number
        // output: N/A
        void setRow(int inRow);

        // Set the appropriate col attributes
        // input: column number
        // output: N/A
        void setCol(int inCol);

        // Get the appropriate row attributes
        // input: N/A
        // output: row number
        int getRow();

        // Get the appropriate column attributes
        // input: N/A
        // output: column number
        int getCol();

        // Add the appropriate row column index of the input to the right
        // attributes of the class object
        // input: a RowColumnClass
        // output: column number
        void addRowColTo(RowColumnClass &intRowCol);

        // Print the row col attributes in the format of "[<row>, <col>]"
        // inout: N/A
        // output: N/A
        void printRowCol();
};

#endif
