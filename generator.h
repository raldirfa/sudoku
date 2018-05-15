#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "sudoku.h"

int solve(SudokuField grid[SUDOKU_SIZE][SUDOKU_SIZE]);
int createRandomPuzzle(SudokuField randomPuzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
void createEmptyFields(SudokuField randomPuzzle[SUDOKU_SIZE][SUDOKU_SIZE]);

#endif // GENERATOR_H_INCLUDED
