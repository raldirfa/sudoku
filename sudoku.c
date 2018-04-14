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

    int i, j, k, l, x;
    static int initCheck[9] = {0,0,0,0,0,0,0,0,0};
    int checkRow[9] = {0,0,0,0,0,0,0,0,0};
    int checkCol[9] = {0,0,0,0,0,0,0,0,0};
    int checkBox[9] = {0,0,0,0,0,0,0,0,0};

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
        for(i = 0; i < SUDOKU_SIZE; i+3){
            for(j = 0; j < SUDOKU_SIZE; j+3){
                memmove(checkBox,initCheck,sizeof(checkBox));
                for(k = 0; k < 3; k++){
                    for(l = 0; l < 3 ; l++){
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

