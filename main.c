#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sudoku.h"
#include "file_operations.h"

int new_game(char path[]);

int main()
{
    char option;
    char path[255];
    int exit = 0;

    do
    {
        system("cls");
        printf("[1] -> Choose Sudoku\n"
               "[2] -> Generate Sudoku\n"
               "[3] -> Load Sudoku\n"
               "[4] -> Import Sudoku form File\n"
               "[x] -> Exit\n\n");
        option = getchar();
        fflush(stdin);
        switch(option)
        {
        case '1':
        case '2':
        case '3':
            new_game("");
            break;
        case '4':
            printf("File name: ");
            scanf("%s", path);
            fflush(stdin);
            new_game(path);
            break;
        case 'x':
            exit = 1;
            break;
        default:
            break;
        }
    } while (!exit);
    return 0;
}

int new_game(char path[])
{
    system("cls");
    int won = 0;
    int error = 0;


    // Level 1 4*4
    /*
    SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {   {{1},{2},{3},{4}},
                                                            {{3},{0},{2},{1}},
                                                            {{2},{1},{4},{3}},
                                                            {{4},{3},{1},{2}}};
    */
    // Level 1 9*9
    SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {   {{7},{9},{0},{0},{5},{8},{2},{0},{0}},
                                                            {{0},{0},{4},{6},{0},{7},{0},{5},{8}},
                                                            {{5},{0},{3},{0},{0},{2},{6},{7},{0}},
                                                            {{0},{4},{0},{2},{7},{0},{5},{0},{6}},
                                                            {{0},{3},{9},{5},{0},{0},{1},{8},{0}},
                                                            {{6},{7},{0},{0},{1},{9},{0},{0},{2}},
                                                            {{9},{0},{0},{7},{0},{1},{0},{0},{4}},
                                                            {{0},{6},{8},{0},{0},{5},{7},{0},{0}},
                                                            {{3},{0},{7},{4},{8},{0},{0},{2},{5}}};

    //Level 1 Solution
    /*
    SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE] = {   {{7},{9},{6},{3},{5},{8},{2},{4},{1}},
                                                            {{1},{2},{4},{6},{9},{7},{3},{5},{8}},
                                                            {{5},{8},{3},{1},{4},{2},{6},{7},{9}},
                                                            {{8},{4},{1},{2},{7},{3},{5},{9},{6}},
                                                            {{2},{3},{9},{5},{6},{4},{1},{8},{7}},
                                                            {{6},{7},{5},{8},{1},{9},{4},{3},{2}},
                                                            {{9},{5},{2},{7},{3},{1},{8},{6},{4}},
                                                            {{4},{6},{8},{9},{2},{5},{7},{1},{3}},
                                                            {{3},{1},{7},{4},{8},{6},{9},{2},{5}}};
    */

    if (strlen(path) != 0)
    {
        int arrayFile[SUDOKU_BOARD_SIZE + 1];
        error = read_file_and_fill_array(arrayFile, path);
        import_to_sudoku(arraySudoku, arrayFile);
    }

    set_editable(arraySudoku);

    int row = 0;
    int column = 0;

    char option[6];
    print_sudoku(arraySudoku);

    time_t now;
    time_t start;
    time(&start);

    do
    {
        if (error == -1) {
            return -1;
        }
        fgets(option, 6 ,stdin);
        //scanf("%s", &option);
        fflush(stdin);

        switch(option[0])
        {
        case 'c':
            if(check_sudoku(arraySudoku) == 1){
                won = 1;
            }else{
                won = -1;
            }
            break;
        case 'h':
            break;
        case 'x':
            return 0;
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

        time(&now);
        double seconds = difftime(now, start);
        printf("%.f seconds have passed since the beginning of the game.\n", seconds);

        if(won == -1){
            printf("Your solution is not correct.\n");
            won = 0;
        } else if(won == 1){
            printf("Congratulations! You won!\n");
        }
        print_sudoku(arraySudoku);
    }

    while(won != 1);
    return 0;
}
