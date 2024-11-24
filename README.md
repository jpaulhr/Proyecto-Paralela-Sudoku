PROYECTO PARALELA 2024

Profesor: Michael Emil Cristi Capstick
Integrantes: 
-Jean Paul Hernández Román
-Jonathan David Ovalle Agurto


Pasos ara la correcta ejecución del programa en Windows:

PASO 1: Descargar MinGW del siguiente link: https://sourceforge.net/projects/mingw/

PASO 2: Se ejecuta el instalador y se hace una descarga normal 
(Solo se debe desmarcar la casilla de ...algo install support for the graphical user interface ya que no lo ocuparemos)

PASO 3: Incluir el la carpeta bin en el path de Windows
Buscador >> Editar variables de entorno del sistema >> Variables de entorno >> Path >> Editar >>Nuevo >> Examinar >>
Buscar la ruta de MinGW (generalmente es C:\MinGW\bin) >> Aceptar hasta salir

PASO 4: Verificar la instalación y descargar mingw-32-make
Abrir consola como administrador >> mingw-get --version (para comprobar si se instaló correctamente) >> mingw-get install mingw32-make >>
Esperar a que se descarguen las dependencias >> en la carpeta C:\MinGW\bin cambiar el nombre "mingw32-make" a "make"

PASO 5: Seguir la guia de https://code.visualstudio.com/docs/cpp/config-mingw para descargar el compilador que se usó

PASO 6: Abrir Visual Studio Code
Descargar extensiones C/C++ , C/C++ Extension Pack y Makefile Tools >> Hacer click en el buscador y escribir ">C/C++:Select IntelliSense Configuration">>
Si todo lo anterior esta correcto debería aparecer la opción de "Use gcc.exe" y lo seleccionamos

PASO 7: Abrir la Terminal
Utilizar el comando "make" para inicializar el programa, debería aparecer esto: 
"gcc -fopenmp -Wall -Wextra -o resolvedor_sudoku main.c sudoku.c json_utils.c cJSON.c"

Luego "./resolvedor_sudoku <archivoEntrada.json> <archivoSalida.json> <cantidadHilos>"

PASO 8: Verificar que el archivoSalida.json se generó en la carpeta del programa y ver si el sudoku está correctamente solucionado.


