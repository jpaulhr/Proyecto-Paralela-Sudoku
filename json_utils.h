#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "cJSON.h"

void leer_json(const char *nombreArchivo, int ***board, int *filas, int *cols);

void escribir_json(const char *nombreArchivo, cJSON *json);

#endif // JSON_UTILS_H
