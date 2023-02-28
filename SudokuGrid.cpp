/*
Author: Mohamed Ghanem
Class: ECE4122A
Last Date Modified: 09/26/2022
Description:
SudokuGrid class used to read in and store sudoku grids from a file, solve them, and output solution to a file.
 */
#include <fstream>
#include "SudokuGrid.h"
using namespace std;
/*
Function that determines if a value is present in a column of a sudoku grid.
*/
bool SudokuGrid::isPresentInCol(int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (gridInt[row][col] == num)
        {
            return true;
        }
    }
    return false;
}
/*
Function that determines if a value is present in a row of a sudoku grid.
*/
bool SudokuGrid::isPresentInRow(int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (gridInt[row][col] == num)
        {
            return true;
        }
    }
    return false;
}
/*
Function that determines if a value is present in a box of a sudoku grid.
*/
bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (gridInt[row+boxStartRow][col+boxStartCol] == num)
            {
                return true;
            }
        }
    }
    return false;
}
/*
Function that determines if there is an empty place in the sudoku grid.
*/
bool SudokuGrid::findEmptyPlace(int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (gridInt[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}
/*
Function that checks if a value is valid in a certain place on the sudoku grid.
*/
bool SudokuGrid::isValidPlace(int row, int col, int num)
{
    return !isPresentInRow(row, num) && !isPresentInCol(col, num)
    && !isPresentInBox(row - row%3 ,col - col%3, num);
}
/*
Helper function that recursively solves a sudoku grid.
*/
bool SudokuGrid::solveSudoku()
{
    int row, col;
    if (!findEmptyPlace(row, col))
    {
        return true;
    }
    for (int num = 1; num <= 9; num++)
    {
        if (isValidPlace(row, col, num))
        {
            gridInt[row][col] = num;
            if (solveSudoku())
            {
                return true;
            }
            gridInt[row][col] = 0;
        }
    }
    return false;
}
/*
Function that performs complete solve of a single sudoku grid.
*/
void SudokuGrid::solve()
{
    charToIntGrid();
    solveSudoku();
    intToCharGrid();
}
/*
Function that converts integer sudoku grid to character sudoku grid.
*/
void SudokuGrid::intToCharGrid()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int num = gridInt[i][j];
            gridElement[i][j] = num + '0';
        }
    }
}
/*
Function that converts character sudoku grid to integer sudoku grid.
*/
void SudokuGrid::charToIntGrid()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char num = gridElement[i][j];
            gridInt[i][j] = num - 48;
        }
    }
}
/*
Function prints sudo grid out to command line for debugging.
*/
void SudokuGrid::printGrid()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << gridElement[i][j];
        }
        cout << "\n";
    }
}
/*
Overloaded >> operator, used to output a single sudoku grid to a file.
*/
fstream& operator>>(fstream& os, SudokuGrid & gridIn)
{
    getline(os, gridIn.m_strGridName);
    string row;
    for (int i = 0; i < 9; i++)
    {
        getline(os, row);
        for (int j = 0; j < 9; j++)
        {
            gridIn.gridElement[i][j] = row[j];
        }
    }
    return os;
}
/*
Overloaded << operator, used to read in a single sudoku grid from a file.
*/
fstream& operator<<(fstream& os, const SudokuGrid & gridOut)
{
    os << gridOut.m_strGridName + "\n";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            os << gridOut.gridElement[i][j];
        }
        os << "\n";
    }
    return os;
}