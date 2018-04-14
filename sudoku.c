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
    printf("\nInput: '$column $row $value' OR 'h' for help OR 'c' to check your solution \n");
}

void print_error(char error[]){

    system("cls");

    printf("%s", error);
    printf("\n");
}

int check_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]){

    int i, j;
    checkRows:{

    }

    checkCols:{
    }

    checkBoxes:{
    }
}

void set_editable(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]){
    int i, j;
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        for (j = 0; j < SUDOKU_SIZE; j++)
        {
            if(arraySudoku[i][j].value == 0){
                arraySudoku[i][j].isEditable = 1;
            } else{
                arraySudoku[i][j].isEditable = 0;
            }

        }
    }
}

