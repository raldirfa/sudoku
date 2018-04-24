#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include <math.h>

// Kann jede beliebige Zahl sein, deren Wurzel eine Ganzzahl ist. Beispiel: 4, 9, 16, 25, 36
#define SUDOKU_SIZE 9
#define SUDOKU_SEPERATOR ((int)sqrt(SUDOKU_SIZE))
#define SUDOKU_BOARD_SIZE (SUDOKU_SIZE * SUDOKU_SIZE)

typedef struct SudokuField
{
    int value;
    int isEditable;
} SudokuField;

void fill_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
void print_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
void print_error(char error[]);
int check_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
void set_editable(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
void import_to_sudoku(SudokuField arraySudoku[SUDOKU_SIZE][SUDOKU_SIZE], int arrayImport[]);

#endif // SUDOKU_H_INCLUDED
