//OBS:
  archivo.c son los archivos de entrada, con -c se compilan.
  -o especifica el nombre del archivo de salida del programa ejecutable.
  -g se debe agregar antes del -c y -o al compilar para usar gdb.
  //Flags:
    -pedantic: Pone a gcc modo pedante, muestra mas cosas para enseñar a usar el lenguaje.
    -std=c99: Chequeda que se programe de acuerdo al estandar del 1999.
    //Flags W:
      Con ellos indicamos como queremos que nos salten las warnings (advertencias).
      -Wall: Muestra todas las advertencias.
      -Werror: Trata a los warnings como errores. 
      -Wextra: Muestra chequeos extras.



//Ejemplo 1:

$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -c main.c
{compila main.c, crea objeto main.o}
$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -o miprograma main.o
{crea el ejectable en miprograma}
$     ./miprograma
{ejecuta miprograma}


Ejecutar con un archivo como input:
$     ./miprograma example-easy.in

Ejecutar leyendo un archivo fuera de la misma carpeta:
$     ./miprograma ../input/example-easy.in

/* 
se le está indicando al programa reader que lea el archivo example-easy.in que para
encontrarlo debe primero subir un nivel (eso indica el .. que se incluye en la ruta o path) y luego entrar en el directorio input.
*/

Ejecutar y desviar la salida en la terminal a un archivo:
$     ./miprograma ../input/example-easy.in > example-easy.out

/*
    ../input/example-easy.in es el parámetro que se le pasa a nuestro programa
weather (el archivo a procesar).
    > example-easy.out hace que la salida del programa, en
vez de mostrarse por la consola, se escriba en el archivo weather_cordoba.out (si no existe se creara y si ya existe se reemplazara).
*/




//Ejemplo 2:    (Compilado en una linea)

$     gcc -Wall  -Werror -Wextra -pedantic -std=c99 -o ej main.c libreria.c
{compila el main y sus librerias si las tiene y crea el ejecutable}
$     ./ejecutable
{ejecuta el programa}


//Ejemplo 3:    (Compilado rapido)

$     gcc -Wall  -Werror -Wextra -pedantic -std=c99 -o ej *.c *.h
{compila el main y sus librerias si las tiene y crea el ejecutable}
$     ./ej
{ejecuta el programa}

/*
La forma de compilar gcc -o ej *.c *.h utiliza el compilador GCC para compilar y enlazar todos los archivos fuente .c y archivos de encabezado .h presentes en el directorio actual en un programa ejecutable llamado ej.

El carácter * se utiliza como comodín para hacer coincidir todos los archivos .c y .h en el directorio actual. Por lo tanto, todos los archivos fuente y de encabezado en el directorio actual se compilarán y enlazarán para formar el programa ejecutable ej.
*/



//Ejemplo 4:    (Main y librerias creadas)

$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -c main.c libreria.c
{Compila el main y la libreria}
$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -o ejecutable main.o libreria.o
{Compila en el ejecutable el programa entero, main necesita la libreria para funcionar}




//Ejemplo 5:    (Con un objeto precompilado)

$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -c main.c libreria.c 
$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -o ejecutable -no-pie main.o precompilado.o libreria.o 

/* 
-no-pie tiene que ver con que se están “linkeando” los objetos main.o y
libreria.o compilados en nuestra computadora con el objeto precompilado precompilado.o, cuya compilación fue
realizada en una computadora distinta. 
En consecuencia esta opción puede ser necesaria para lograr
compatibilidad entre los archivos binarios durante el “linkeo” y así poder generar el ejecutable.
*/

puede ejecutarse de la siguiente manera:
$     ./ejecutable ../input/example-unsorted.in






