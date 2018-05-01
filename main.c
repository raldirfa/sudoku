#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "sudoku.h"
#include "file_operations.h"

int new_game(SudokuField arraySudoku[][SUDOKU_SIZE]);
int init_game(char path[]);

int main()
{
    char path[100];
    int exit = 0;
    int back = 0;

    do
    {
        exit = 0;
        back = 0;
        system("cls");
        printf("[1] -> Choose Sudoku\n"
               "[2] -> Generate Sudoku\n"
               "[3] -> Load Sudoku\n"
               "[4] -> Import Sudoku form File\n"
               "[x] -> Exit\n\n");
        switch(getch())
        {
        case '1':
            do
            {
                system("cls");
                printf("[1] -> Easy\n"
                       "[2] -> Medium\n"
                       "[3] -> Hard\n"
                       "[x] -> Back\n\n");
                switch(getch())
                {
                case '1':
                case '2':
                case '3':
                    init_game("");
                    back = 1;
                    break;
                case 'x':
                    back = 1;
                    break;
                default:
                    break;
                }
            } while (!back);
            break;
        case '2':
        case '3':
            init_game("");
            break;
        case '4':
            printf("Files:\n");
            system("dir " SUBFOLDER " /b");
            printf("\nFile name: ");
            gets(path);
            fflush(stdin);
            init_game(path);
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

int new_game(SudokuField arraySudoku[][SUDOKU_SIZE])
{
    int won = 0;
    int value = 0;
    Cursor cursor = {0, 0};

    time_t now;
    time_t start;
    time(&start);
    double seconds;

    do
    {
        system("cls");
        time(&now);
        seconds = difftime(now, start);
        printf("%.f seconds have passed since the beginning of the game.\n\n", seconds);

        print_sudoku(arraySudoku, cursor);
        switch(getch())
        {
        case 'c':
            won = check_sudoku(arraySudoku);
            if (!won)
            {
                printf("Your solution is not correct.\n");
                system("pause");
            }
            break;
        case 'h':
            printf("No help!!!");
            break;
        case 'x':
            printf("Are you sure you want to quit? y/n");
            switch(getch())
            {
            case 'y':
                return 0;
                break;
            default:
                break;
            }
            break;
        case 'H':
        case 'w':
            cursor.y--;
            break;
        case 'K':
        case 'a':
            cursor.x--;
            break;
        case 'P':
        case 's':
            cursor.y++;
            break;
        case 'M':
        case 'd':
            cursor.x++;
            break;
        case 13:
            if ( arraySudoku[cursor.y][cursor.x].isEditable)
            {
                printf("Value to insert: ");
                fflush(stdin);
                scanf("%d", &value);
                fflush(stdin);
                if (value <= SUDOKU_SIZE)
                {
                    arraySudoku[cursor.y][cursor.x].value = value;
                }
            }
            break;
        default:
            break;
        }
        check_and_move_sudoku_cursor(&cursor);
    } while(won != 1);
    printf("Congratulations! You won!\nSeconds: %.f\n", seconds);
    system("pause");
    return 0;
}

int init_game(char path[])
{
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

    if (strlen(path) != 0)
    {
        int arrayFile[SUDOKU_BOARD_SIZE + 1];
        // Workaround: Variable get random values
        if(read_file_and_fill_array(arrayFile, path))
        {
            return 1;
        }
        import_to_sudoku(arraySudoku, arrayFile);
    }

    set_editable(arraySudoku);
    new_game(arraySudoku);
    return 0;
}
