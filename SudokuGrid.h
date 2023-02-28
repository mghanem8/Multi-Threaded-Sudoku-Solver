/*
Author: Mohamed Ghanem
Class: ECE4122A
Last Date Modified: 09/26/2022
Description:
SudokuGrid header file used to define all variables and function for SudokuGrid class.
 */
#include <iostream>
using namespace std;
class SudokuGrid
{
    string m_strGridName; // string that will store grid name
    unsigned char gridElement[9][9]; // char array that store sudoku grid
    unsigned int gridInt[9][9]; // int array that store sudoku grid

    void charToIntGrid(); // function to convert char grid to int grid
    void intToCharGrid(); // function to int char grid to char grid
    //helper functions for solving sudoku grid
    bool solveSudoku();
    bool isPresentInCol(int col, int num);
    bool isPresentInRow(int row, int num);
    bool isPresentInBox(int boxStartRow, int boxStartCol, int num);
    bool findEmptyPlace(int &row, int &col);
    bool isValidPlace(int row, int col, int num);
public:
    // overloaded stream operators
    friend fstream& operator>>(fstream& os, SudokuGrid & gridIn);
    friend fstream& operator<<(fstream& os, const SudokuGrid & gridOut);
    void solve(); // function to solve sudoku grid
    void printGrid(); // function to print grid to command line for debugging
};
