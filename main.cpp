/*
Author: Mohamed Ghanem
Class: ECE4122A
Last Date Modified: 09/26/2022
Description:
Main file used to check input file, run multithreaded program, and create output file.
 */
#include <mutex>
#include <fstream>
#include <thread>
#include "SudokuGrid.h"
using namespace std;
// initialize inout and output file mutexs
mutex outFileMutex;
mutex inFileMutex;
// initialize inout and output file global streams
fstream outFile;
fstream inFile;
/*
Function solveSudokuPuzzle will read in one puzzle from the input file,
solve it, then output the result to the output file.
 */
void solveSudokuPuzzles()
{

    SudokuGrid sudokuGrid; // initialize sudokuGrid
    do
    {
        if (inFile.eof()) // break if end of file has been reached
        {
            break;
        }
        else
        {
            inFileMutex.lock(); // lock input stream
            inFile >> sudokuGrid; // read in a single sudoku grid from input file
            inFileMutex.unlock(); //unlock input stream
            sudokuGrid.solve(); // solve current sudoku grid
            outFileMutex.lock(); // lock output file mutex
            outFile << sudokuGrid; // write in a single sudoku grid to output file
            outFileMutex.unlock(); // unlock output stream
        }
    } while (!inFile.eof()); // check if end of file has been reached
}
/*
 main function
 */
int main (int argc, char *argv[])
{
    inFile.open(argv[1], fstream::in); // open input file
    if (inFile.fail()) // check if input file has been opened successfully
    {
        cout << "Invalid Input File!" << endl; // output invalid prompt
    }
    else
    {
        outFile.open("Lab2Prob2.txt", fstream::out); // create new output file
        unsigned int numThreads = 1; // check number of concurrent hardware threads
        thread threads[numThreads - 1]; // initialize thread array
        for (int i = 0; i < numThreads - 1; i++)
        {
            threads[i] = thread(solveSudokuPuzzles); // populate thread array with solveSudokuPuzzles function
        }
        solveSudokuPuzzles();
        for (int i = 0; i < numThreads - 1; i++)
        {
            threads[i].join(); // join threads when they are finished
        }
        inFile.close(); // close input file
        outFile.close(); // close output file
    }
    return 0;
}