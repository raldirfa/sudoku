#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_operations.h"

// From https://stackoverflow.com/a/3463793
// Load a file and convert to an array
int read_file_and_fill_array(int arrayToFill[], char filepath[])
{
    FILE *file;
    int c;
    int i = 0;

    file = fopen(filepath, "r");
    if (file)
    {
        while ((c = getc(file)) != EOF)
        {
            if (c != '\n')
            {
                arrayToFill[i] = c - 48;
                i++;
            }
        }
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

// Saves the complete Sudoku struct in a ".chan" file. The filename can be determined by the user
int save_sudoku(SudokuField arrayToSave[SUDOKU_SIZE][SUDOKU_SIZE], char filename[])
{
    FILE *outfile;
    int i,j;
    char path[100];

    strcpy(path, SAVEFOLDER);
    strcat(path, filename);
    strcat(path, ".chan");

    outfile = fopen (path, "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    for(i = 0; i < SUDOKU_SIZE; i++)
    {
        for(j = 0; j < SUDOKU_SIZE; j++)
        {
            fwrite (&arrayToSave[i][j], sizeof(SudokuField), 1, outfile);
        }
    }

    fclose(outfile);
    return 0;
}

// Loads a previously saved Sudoku
int load_sudoku(char filepath[], SudokuField sudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    FILE *file;
    int i = 0;
    SudokuField input;

    file = fopen (filepath, "r");

    if (file == NULL)
    {
        return 1;
    }

    while(fread(&input, sizeof(SudokuField), 1, file))
    {
        sudoku[i/SUDOKU_SIZE][i%SUDOKU_SIZE] = input;
        i++;
    }

    return 0;
}

// Shows the user possible files
int get_path(char path[], char folder[])
{
    char temp[100];
    char systemDirectory[100];

    strcpy(systemDirectory, "dir ");
    strcat(systemDirectory, folder);
    strcat(systemDirectory, " /b");

    printf("Files:\n");
    system(systemDirectory);
    printf("\nFile name: ");
    gets(temp);
    strcpy(path, folder);
    strcat(path, temp);
    fflush(stdin);

    return 0;
}





