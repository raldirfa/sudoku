#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include "sudoku.h"

#define SUBFOLDER "level\\"
#define SAVEFOLDER "saves\\"

int read_file_and_fill_array(int arrayToFill[], char filename[]);
int save_sudoku(SudokuField arrayToSave[SUDOKU_SIZE][SUDOKU_SIZE], char filepath[]);
int load_sudoku(char filepath[],SudokuField sudoku[SUDOKU_SIZE][SUDOKU_SIZE]);
int get_path(char path[], char folder[]);

#endif // FILE_OPERATIONS_H_INCLUDED
