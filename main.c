#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"

int main()
{
    struct SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE];
    int won = 0;

    fill_sudoku(arraySudoku);

    //Spiel 1
    {
        arraySudoku[0][0].value = 7;
        arraySudoku[0][1].value = 9;
        arraySudoku[0][4].value = 5;
        arraySudoku[0][5].value = 8;
        arraySudoku[0][6].value = 2;

        arraySudoku[1][2].value = 4;
        arraySudoku[1][3].value = 6;
        arraySudoku[1][5].value = 7;
        arraySudoku[1][7].value = 5;
        arraySudoku[1][8].value = 8;

        arraySudoku[2][0].value = 5;
        arraySudoku[2][2].value = 3;
        arraySudoku[2][5].value = 2;
        arraySudoku[2][6].value = 6;
        arraySudoku[2][7].value = 7;

        arraySudoku[3][1].value = 4;
        arraySudoku[3][3].value = 2;
        arraySudoku[3][4].value = 7;
        arraySudoku[3][6].value = 5;
        arraySudoku[3][8].value = 6;

        arraySudoku[4][1].value = 3;
        arraySudoku[4][2].value = 9;
        arraySudoku[4][3].value = 5;
        arraySudoku[4][6].value = 1;
        arraySudoku[4][7].value = 8;

        arraySudoku[5][0].value = 6;
        arraySudoku[5][1].value = 7;
        arraySudoku[5][4].value = 1;
        arraySudoku[5][5].value = 9;
        arraySudoku[5][8].value = 2;

        arraySudoku[6][0].value = 9;
        arraySudoku[6][3].value = 7;
        arraySudoku[6][5].value = 1;
        arraySudoku[6][8].value = 4;

        arraySudoku[7][1].value = 6;
        arraySudoku[7][2].value = 8;
        arraySudoku[7][5].value = 5;
        arraySudoku[7][6].value = 7;

        arraySudoku[8][0].value = 3;
        arraySudoku[8][2].value = 7;
        arraySudoku[8][3].value = 4;
        arraySudoku[8][4].value = 8;
        arraySudoku[8][7].value = 2;
        arraySudoku[8][8].value = 5;

    }
    set_editable(arraySudoku);

    int row = 0;
    int column = 0;

    char option[6];
    print_sudoku(arraySudoku);


    do
    {
        fgets(option, 6 ,stdin);
        //scanf("%s", &option);
        fflush(stdin);

        switch(option[0])
        {
        case 'h':
            break;
        case 'c':
            if(check_sudoku(arraySudoku) == 1){
                won = 1;
            }else{
                won = -1;
            }
            break;
        default:
            //TODO: Anpassen check if option[0,2,4] is a number and if option[1,3] is blank

            if(option[0] >= '1' && option[0] <= '9'){
                column = option[0]-48;
            } else{
                print_error("ERROR: Incorrect input!");
                print_sudoku(arraySudoku);
                continue;
            }
            if(option[2] >= '1' && option[2] <= '9'){
                row = option[2]-48;
            } else{
                print_error("ERROR: Incorrect input!");
                print_sudoku(arraySudoku);
                continue;
            }
            if(option[4] >= '0' && option[4] <= '9'){

                if(arraySudoku[row-1][column-1].isEditable == 1){
                    arraySudoku[row-1][column-1].value = option[4]-48;
                }else{
                    print_error("You can't edit this field");
                    print_sudoku(arraySudoku);
                    continue;
                }

            } else{
                print_error("ERROR: Incorrect input!");
                print_sudoku(arraySudoku);
                continue;
            }
        }
        system("cls");
        if(won == -1){
            printf("Your solution is not correct.\n");
            won = 0;
        } else if(won == 1){
            printf("Congratulations! You won!\n");
        }
        print_sudoku(arraySudoku);
    }

    while(won != 1);
}
