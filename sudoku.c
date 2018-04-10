#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

void fill_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int i, j;
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        for (j = 0; j < SUDOKU_SIZE; j++)
        {
            arraySudoku[i][j].value = 0;
        }
    }
}

void print_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    int i, j;
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        if(i%3 == 0)
        {
            printf("+---------+---------+---------+\n");
        }
        for (j = 0; j < SUDOKU_SIZE; j++)
        {
            if(j%3 == 0)
            {
                printf("|");
            }
            printf(" %d ", arraySudoku[i][j].value);
        }

        printf("|\n");
    }
    printf("+---------+---------+---------+\n");
}

