#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include "sudoku.h"

#define SUBFOLDER "level\\"
#define SAVEFOLDER "saves\\"

int read_file_and_fill_array(int arrayToFill[], char filepath[]);
int save_sudoku(SudokuField arrayToSave[SUDOKU_SIZE][SUDOKU_SIZE]);
int load_sudoku(char filepath[],SudokuField sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);

#endif // FILE_OPERATIONS_H_INCLUDED
