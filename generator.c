#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generator.h"

#define UNASSIGNED 0

int is_valid(SudokuField sudoku[SUDOKU_SIZE][SUDOKU_SIZE], int row, int col, int number)
{
    int isOk = 1;
    int cCol=0,cRow=0;

    for (cCol = 0; cCol < SUDOKU_SIZE; cCol++)
    {
        if (sudoku[row][cCol].value == number)
        {
            isOk = 0;
        }
    }

    for (cRow = 0; cRow < SUDOKU_SIZE; cRow++)
    {
        if (sudoku[cRow][col].value == number)
        {
            isOk = 0;
        }
    }

    int aRow = row;
    int aCol = col;
    row=0;
    col=0;
    for ( row = 0; row < SUDOKU_SEPERATOR; row++)
    {
        for ( col = 0; col < SUDOKU_SEPERATOR; col++)
        {
            if (sudoku[row + (aRow-(aRow%SUDOKU_SEPERATOR))][col + (aCol-(aCol%SUDOKU_SEPERATOR))].value == number)
            {
                isOk = 0;
            }
        }
    }
    return isOk;
}

void createEmptyFields(SudokuField randomPuzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int counter = 0;
    int randomRow = 0;
    int randomCol = 0;
    srand(time(NULL));
    while(counter < 40)
    {
        counter++;
        randomRow = (rand() % SUDOKU_SIZE);
        randomCol = (rand() % SUDOKU_SIZE);
        if(randomPuzzle[randomRow][randomCol].value !=0)
        {
            randomPuzzle[randomRow][randomCol].value =0;
        }
        else
        {
            counter--;
        }
    }
}


int createRandomPuzzle(SudokuField randomPuzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    srand(time(NULL));
    int randomRow =0;
    int randomCol=0;
    int randomNum=0;

    int counter =0;

    while(counter < 15)
    {
        counter++;
        randomRow = (rand() % SUDOKU_SIZE);
        randomCol = (rand() % SUDOKU_SIZE);
        randomNum = (rand() % SUDOKU_SIZE)+1;

        if(randomPuzzle[randomRow][randomCol].value == 0 && randomPuzzle[randomRow][randomCol].value != randomNum && is_valid(randomPuzzle,randomRow,randomCol,randomNum) == 1)
        {
            randomPuzzle[randomRow][randomCol].value = randomNum;
        }

        else
        {
            counter--;
        }


    }

    return 0;

}

//Ab hier :https://gist.github.com/bopbi/c9f94b1b981b84bcb02b
int find_unassigned(SudokuField grid[SUDOKU_SIZE][SUDOKU_SIZE], int *row, int *col)
{
    for (*row = 0; *row < SUDOKU_SIZE; (*row)++)
    {
        for (*col = 0; *col < SUDOKU_SIZE; (*col)++)
        {
            if (grid[*row][*col].value == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int solve(SudokuField grid[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int row = 0;
    int col = 0;

    if (!find_unassigned(grid, &row, &col))
    {
        return 1;
    }

    int num =1;
    for ( num = 1; num <= SUDOKU_SIZE; num++ )
    {

        if (is_valid(grid, row, col, num))
        {
            grid[row][col].value = num;

            if (solve(grid))
            {
                return 1;
            }

            grid[row][col].value = UNASSIGNED;
        }
    }

    return 0;
}
