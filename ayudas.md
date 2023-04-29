//Compilar archivos terminados en .o
gcc -Wall -Werror -Wextra -pedantic -std=c99 -c <NOMBRE_DEL_ARCHIVO.c>

//Compilar archivos usando otros
gcc -Wall -Werror -Wextra -pedantic -std=c99 <NOMBRE_DEL_ARCHIVO_1.o> <NOMBRE_DEL_ARCHIVO_1.o> -o <NOMBRE_DEL_ARCHIVO_FINAL>





//Comando para comprirmir
tar -czvf <NOMBRE_DEL_ARCHIVO_COMPRIMIDO.tar.gz> <CARPETA_QUE_SE_COMPRIME>

//Comando para descomprimir
tar -xf <NOMBRE_DEL_ARCHIVO_COMPRIMIDO.tar.gz>
