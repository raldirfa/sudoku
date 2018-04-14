#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#define SUDOKU_SIZE 9

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

#endif // SUDOKU_H_INCLUDED
