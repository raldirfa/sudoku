#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

// Static functions

static void fill_checkArray(int array[SUDOKU_SIZE])
{
    int i;
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        array[i] = 0;
    }
}

static void print_horizontal_seperator()
{
    int i, j;
    for (i = 0; i < SUDOKU_SEPERATOR; i++)
    {
        printf("+");
        for (j = 0; j < SUDOKU_SEPERATOR * 3; j++)
        {
            printf("-");
        }
    }
    printf("+\n");
}

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

void print_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE], Cursor cursor)
{
    int i, j;
    for (i = 0; i < SUDOKU_SIZE; i++)
    {
        if(i%SUDOKU_SEPERATOR == 0)
        {
            print_horizontal_seperator();
        }
        for (j = 0; j < SUDOKU_SIZE; j++)
        {
            if(j%SUDOKU_SEPERATOR == 0)
            {
                printf("|");
            }
            if (i == cursor.y && j == cursor.x)
            {
                printf("\x1b[32m");
            }
            if(arraySudoku[i][j].value != 0){
                if (arraySudoku[i][j].value > 9)
                {
                    printf("%d ", arraySudoku[i][j].value);
                }
                else
                {
                    printf(" %d ", arraySudoku[i][j].value);
                }
            } else{
                printf(" . ");
            }
            printf("\x1b[0m");
        }

        printf("|\n");
    }
    print_horizontal_seperator();
    printf("\nInput:\n"
           "Use the Arrowkeys or WASD to move.\n"
           "[h] for help\n"
           "[c] to check your solution\n"
           "[x] to exit the game\n\n");
}

int check_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]){

    int i, j, k, l, x;
    int checkArray[SUDOKU_SIZE];
    fill_checkArray(checkArray);

    //checkRows:
    {
        for(i = 0; i < SUDOKU_SIZE; i++){
            fill_checkArray(checkArray);
            for(j = 0; j < SUDOKU_SIZE; j++){
                x = arraySudoku[i][j].value;
                if(x == 0){
                    return 0;
                }
                if( checkArray[x-1] == 0){
                    checkArray[x-1] = 1;
                } else {
                    return 0;
                }

            }
        }
    }

    //checkCols:
    {
        for(i = 0; i < SUDOKU_SIZE; i++){
            fill_checkArray(checkArray);
            for(j = 0; j < SUDOKU_SIZE; j++){
                x = arraySudoku[j][i].value;
                if(x == 0){
                    return 0;
                }
                if( checkArray[x-1] == 0){
                    checkArray[x-1] = 1;
                } else {
                    return 0;
                }

            }
        }
    }

    //checkBoxes:
    {
        //i and j point to the first field in every 3x3 box
        //k and l iterate through every field in the box
        for(i = 0; i < SUDOKU_SIZE; i = i + SUDOKU_SEPERATOR){
            for(j = 0; j < SUDOKU_SIZE; j = j + SUDOKU_SEPERATOR){
                fill_checkArray(checkArray);
                for(k = 0; k < SUDOKU_SEPERATOR; k++){
                    for(l = 0; l < SUDOKU_SEPERATOR; l++){
                        x = arraySudoku[i+k][j+l].value;
                        if(x == 0){
                            return 0;
                        }
                        if( checkArray[x-1] == 0){
                            checkArray[x-1] = 1;
                        } else {
                            return 0;
                        }

                    }
                }
            }
        }
    }
    return 1;
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

/*
    Using the property of integers to only return integers when divided
    this loop copies a 1 dimensional array into a 2 dimensional array.
*/
void import_to_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE], int arrayImport[])
{
    int i;
    for (i = 0; i < SUDOKU_BOARD_SIZE + 1; i++)
    {
        arraySudoku[i/SUDOKU_SIZE][i%SUDOKU_SIZE].value = arrayImport[i];
    }
}
