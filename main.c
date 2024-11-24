#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "sudoku.h"
#include "json_utils.h"

int main(int argc, char *argv[]) {
    //Permitir que se indique el archivo de entrada y salida con el numero de hilos que se quiere resolver
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <archivo_entrada.json> <archivo_salida.json> <numero_hilos>\n", argv[0]);
        return 1;
    }

    const char *archivo_entrada = argv[1];
    const char *archivo_salida = argv[2];
    int num_hilos = atoi(argv[3]); // Leer el número de hilos del argumento

    if (num_hilos <= 0) {
        fprintf(stderr, "Número de hilos inválido: %d\n", num_hilos);
        return 1;
    }

    int **board;
    int filas, cols;

    // Leer el JSON de entrada
    leer_json(archivo_entrada, &board, &filas, &cols);

    // Configurar el número de hilos
    omp_set_num_threads(num_hilos);

    // Resolver el Sudoku
    double inicio = omp_get_wtime(); // Medir tiempo de inicio
    resolver_sudoku(board, filas, cols);
    double fin = omp_get_wtime();    // Medir tiempo de finalización

    // Convertir y guardar el resultado
    cJSON *json = sudoku_a_json(board, filas, cols);
    escribir_json(archivo_salida, json);

    // Mostrar el tiempo total
    printf("Tiempo total con %d hilos: %.2f segundos\n", num_hilos, fin - inicio);

    // Liberar memoria
    cJSON_Delete(json);
    for (int i = 0; i < filas; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}