#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_operations.h"

// From https://stackoverflow.com/a/3463793
int read_file_and_fill_array(int arrayToFill[], char filepath[])
{
    FILE *file;
    int c;
    int i = 0;
    char path[100];

    strcpy(path, SUBFOLDER);
    strcat(path, filepath);

    file = fopen(path, "r");
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

int load_sudoku(char filepath[],SudokuField sudoku[SUDOKU_SIZE][SUDOKU_SIZE])
{
    FILE *infile;
    int i = 0;
    SudokuField input;

    infile = fopen (filepath, "r");

    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return 1;
    }

    while(fread(&input, sizeof(SudokuField), 1, infile))
    {

        sudoku[i/9][i%9] = input;
        i++;
    }

    return 0;
}






