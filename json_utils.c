#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "json_utils.h"

// Función para leer un archivo JSON y convertirlo en una matriz de enteros
void leer_json(const char *nombreArchivo, int ***board, int *filas, int *cols) {
    // Abre el archivo JSON para lectura
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo JSON");
        return;
    }

    // Mueve el puntero del archivo al final para calcular el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Asigna memoria para el contenido del archivo y lo lee
    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, archivo);
    fclose(archivo);

    // Asegura que el contenido del archivo termina en NULL
    data[length] = '\0';

    // Parsea el contenido del archivo JSON
    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        printf("Error al validar el archivo JSON\n");
        free(data);
        return;
    }

    // Obtiene el objeto "board" del JSON
    cJSON *tablero_json = cJSON_GetObjectItemCaseSensitive(json, "board");
    if (!cJSON_IsArray(tablero_json)) {
        printf("Formato del archivo JSON invalido\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    // Obtiene el número de filas y columnas del tablero
    *filas = cJSON_GetArraySize(tablero_json);
    *cols = cJSON_GetArraySize(cJSON_GetArrayItem(tablero_json, 0));

    // Asigna memoria para la matriz del tablero y la llena con los datos del JSON
    *board = malloc(*filas * sizeof(int *));
    for (int i = 0; i < *filas; i++) {
        (*board)[i] = malloc(*cols * sizeof(int));
        cJSON *fila = cJSON_GetArrayItem(tablero_json, i);
        for (int j = 0; j < *cols; j++) {
            cJSON *celda = cJSON_GetArrayItem(fila, j);
            (*board)[i][j] = celda->valueint;
        }
    }

    // Libera la memoria del JSON parseado y del contenido del archivo
    cJSON_Delete(json);
    free(data);
}

// Función para escribir una matriz de enteros en un archivo JSON
void escribir_json(const char *nombreArchivo, cJSON *json) {
    // Abre el archivo JSON para escritura
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Usa cJSON_Print para obtener el JSON en formato "pretty" (legible)
    char *string = cJSON_Print(json);
    if (string == NULL) {
        fprintf(stderr, "Error: no se pudo generar el JSON\n");
        fclose(archivo);
        return;
    }

    // Escribe el JSON formateado al archivo
    fprintf(archivo, "%s\n", string);
    fclose(archivo);

    // Libera la memoria del string generado
    free(string);
}
