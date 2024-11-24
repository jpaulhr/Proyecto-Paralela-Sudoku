#ifndef SUDOKU_H
#define SUDOKU_H
#include "cJSON.h"


void resolver_sudoku(int **board, int filas, int cols);
cJSON* sudoku_a_json(int **board, int filas, int cols);

#endif // SUDOKU_H
