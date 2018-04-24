#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

// Static functions

static void fill_check_array(int array[SUDOKU_SIZE])
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

void print_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE])
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
                printf("   ");
            }

        }

        printf("|\n");
    }
    print_horizontal_seperator();
    printf("\nInput:\n"
           "[$column $row $value]\n"
           "[h] for help\n"
           "[c] to check your solution\n"
           "[x] to exit the game\n\n");
}

void print_error(char error[]){

    system("cls");

    printf("%s", error);
    printf("\n");
}

int check_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]){

    int i, j, k, l, x;
    static int initCheck[SUDOKU_SIZE];
    int checkRow[SUDOKU_SIZE];
    int checkCol[SUDOKU_SIZE];
    int checkBox[SUDOKU_SIZE];

    fill_check_array(initCheck);
    fill_check_array(checkRow);
    fill_check_array(checkCol);
    fill_check_array(checkBox);

    //checkRows:
    {
        for(i = 0; i < SUDOKU_SIZE; i++){
            memmove(checkRow,initCheck,sizeof(checkRow));
            for(j = 0; j < SUDOKU_SIZE; j++){
                x = arraySudoku[i][j].value;
                if(x == 0){
                    return 0;
                }
                if( checkRow[x-1] == 0){
                    checkRow[x-1] = 1;
                } else {
                    return 0;
                }

            }
        }
    }

    //checkCols:
    {
        for(i = 0; i < SUDOKU_SIZE; i++){
            memmove(checkCol,initCheck,sizeof(checkCol));
            for(j = 0; j < SUDOKU_SIZE; j++){
                x = arraySudoku[j][i].value;
                if(x == 0){
                    return 0;
                }
                if( checkCol[x-1] == 0){
                    checkCol[x-1] = 1;
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
                memmove(checkBox,initCheck,sizeof(checkBox));
                for(k = 0; k < SUDOKU_SEPERATOR; k++){
                    for(l = 0; l < SUDOKU_SEPERATOR; l++){
                        x = arraySudoku[i+k][j+l].value;
                        if(x == 0){
                            return 0;
                        }
                        if( checkBox[x-1] == 0){
                            checkBox[x-1] = 1;
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
