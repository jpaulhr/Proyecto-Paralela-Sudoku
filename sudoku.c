#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include "sudoku.h"
#include "cJSON.h"
#include "json_utils.h"

// Función para verificar si un número está en un bloque
bool esta_en_el_bloque(int **board, int filaInicial, int columInicial, int num, int tamBloque) {
    for (int i = 0; i < tamBloque; i++) {
        for (int j = 0; j < tamBloque; j++) {
            if (board[filaInicial + i][columInicial + j] == num) {
                return true;
            }
        }
    }
    return false;
}

// Función para verificar si un número está en una fila o columna específica
bool esta_en_fila_o_columna(int **board, int fila, int col, int num, int tamTablero) {
    for (int i = 0; i < tamTablero; i++) {
        if (board[fila][i] == num || board[i][col] == num) {
            return true;
        }
    }
    return false;
}

// Función para verificar si un número es válido en una celda específica
bool validar_celda(int **board, int fila, int col, int num, int tamTablero) {
    int tamBloque = (int)sqrt(tamTablero);
    return !esta_en_fila_o_columna(board, fila, col, num, tamTablero) &&
           !esta_en_el_bloque(board, fila - fila % tamBloque, col - col % tamBloque, num, tamBloque);
}

// Función para resolver el Sudoku usando backtracking paralelizado
bool resolver_sudoku_recursivamente(int **board, int tamTablero) {
    // Recorre cada celda del tablero
    for (int fila = 0; fila < tamTablero; fila++) {
        for (int col = 0; col < tamTablero; col++) {
            // Encuentra una celda vacía
            if (board[fila][col] == 0) {
                int solucion_encontrada = 0; // Variable compartida para indicar solución encontrada

                // Paralelizar el intento de números
                #pragma omp parallel for shared(solucion_encontrada)
                for (int num = 1; num <= tamTablero; num++) {
                    // Verificar si otro hilo ya encontró la solución
                    if (solucion_encontrada) {
                        continue;
                    }

                    // Validar el número en la celda
                    if (validar_celda(board, fila, col, num, tamTablero)) {
                        // Crear una copia del tablero para evitar conflictos entre hilos
                        int **copia_tablero = (int **)malloc(tamTablero * sizeof(int *));
                        for (int i = 0; i < tamTablero; i++) {
                            copia_tablero[i] = (int *)malloc(tamTablero * sizeof(int));
                            for (int j = 0; j < tamTablero; j++) {
                                copia_tablero[i][j] = board[i][j];
                            }
                        }

                        copia_tablero[fila][col] = num;

                        // Llamada recursiva en el tablero copiado
                        if (resolver_sudoku_recursivamente(copia_tablero, tamTablero)) {
                            #pragma omp critical
                            {
                                if (!solucion_encontrada) {
                                    // Copiar la solución al tablero original
                                    for (int i = 0; i < tamTablero; i++) {
                                        for (int j = 0; j < tamTablero; j++) {
                                            board[i][j] = copia_tablero[i][j];
                                        }
                                    }
                                    solucion_encontrada = 1;
                                }
                            }
                        }

                        // Liberar la memoria del tablero copiado
                        for (int i = 0; i < tamTablero; i++) {
                            free(copia_tablero[i]);
                        }
                        free(copia_tablero);
                    }
                }

                return solucion_encontrada; // Indicar si se encontró una solución
            }
        }
    }
    return true; // Sudoku resuelto
}

// Función principal para resolver el Sudoku
void resolver_sudoku(int **board, int filas, int cols) {
    if (filas != cols) {
        printf("Dimensión del tablero no soportada\n");
        return;
    }

    // Resolver el Sudoku
    if (!resolver_sudoku_recursivamente(board, filas)) {
        printf("No existe solución\n");
    }
}

// Función para convertir el tablero de Sudoku a formato JSON
cJSON* sudoku_a_json(int **board, int filas, int cols) {
    cJSON *root = cJSON_CreateObject(); // Crear objeto root JSON
    cJSON *tablero_json = cJSON_CreateArray(); // Crear array para el tablero

    // Convertir cada fila del tablero en un array JSON
    for (int i = 0; i < filas; i++) {
        cJSON *fila = cJSON_CreateIntArray(board[i], cols);
        cJSON_AddItemToArray(tablero_json, fila);
    }

    cJSON_AddItemToObject(root, "board", tablero_json); // Agregar el array del tablero al objeto root
    return root;
}
