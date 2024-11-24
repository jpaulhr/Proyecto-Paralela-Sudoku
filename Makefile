# Definir el compilador a utilizar
CC = gcc

# Definir las banderas del compilador
# -fopenmp: Activar el soporte para OpenMP para paralelismo
# -Wall: Habilitar todos los mensajes de advertencia
# -Wextra: Habilitar advertencias adicionales que no están habilitadas por -Wall
CFLAGS = -fopenmp -Wall -Wextra

# Definir los archivos fuente
SOURCES = main.c sudoku.c json_utils.c cJSON.c

# Definir el nombre del archivo ejecutable
TARGET = resolvedor_sudoku

# La regla 'all' compila el objetivo principal
all: $(TARGET)

# La regla para compilar el objetivo
# $@: Nombre del objetivo (TARGET)
# $^: Todos los archivos de dependencia (SOURCES)
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

# La regla 'clean' elimina archivos objeto y el ejecutable
clean:
	rm -f *.o $(TARGET)
