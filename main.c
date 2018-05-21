#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "sudoku.h"
#include "file_operations.h"

int new_game(SudokuField arraySudoku[][SUDOKU_SIZE]);
int get_path(char path[], char folder[]);
int init_game(int difficulty);
int init_game_path(char path[]);

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
        printf("[1] -> Generate Sudoku\n"
               "[2] -> Load Sudoku\n"
               "[3] -> Import Sudoku form File\n"
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
                    init_game(1);
                    back = 1;
                    break;
                case '2':
                    init_game(2);
                    back = 1;
                    break;
                case '3':
                    init_game(3);
                    back = 1;
                    break;
                case 'x':
                    back = 1;
                    break;
                default:
                    break;
                }
            }
            while (!back);
            break;
        case '2':
            get_path(path, SAVEFOLDER);
            init_game_path(path);
            break;
        case '3':
            get_path(path, SUBFOLDER);
            init_game_path(path);
            break;
        case 'x':
            exit = 1;
            break;
        default:
            break;
        }
    }
    while (!exit);
    return 0;
}

int new_game(SudokuField arraySudoku[][SUDOKU_SIZE])
{
    int won = 0;
    int value = 0;
    Cursor cursor = {0, 0};

    char filename[100];
    char message[100] = "";

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

        print_sudoku(arraySudoku, cursor, message);

        strcpy(message, "");
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
        case 'S':
            printf("Are you sure you want to save? y/n\n");
            switch(getch())
            {
            case 'y':
                printf("Filename: ");
                gets(filename);
                fflush(stdin);
                save_sudoku(arraySudoku, filename);
                return 0;
                break;
            default:
                break;
            }
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
            else
            {
                strcat(message, "Field is not editable!");
            }
            break;
        default:
            break;
        }
        check_and_move_sudoku_cursor(&cursor);
    }
    while(won != 1);
    printf("Congratulations! You won!\nSeconds: %.f\n", seconds);
    system("pause");
    return 0;
}

int init_game(int difficulty)
{
    SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE];
    fill_sudoku(arraySudoku);
    generateSudoku(arraySudoku, difficulty);
    set_editable(arraySudoku);
    new_game(arraySudoku);
    return 0;
}

int init_game_path(char path[])
{
    SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE];
    int loaded = 0;

    if (strlen(path) != 0)
    {
        if (strstr(path, SAVEFOLDER) != NULL)
        {
            if(load_sudoku(path, arraySudoku))
            {
                return 1;
            }
            loaded = 1;
        }
        else
        {
            int arrayFile[SUDOKU_BOARD_SIZE + 1];
            if(read_file_and_fill_array(arrayFile, path))
            {
                return 1;
            }
            import_to_sudoku(arraySudoku, arrayFile);
        }
    }

    if(!loaded)
    {
        set_editable(arraySudoku);
    }

    new_game(arraySudoku);
    return 0;
}
