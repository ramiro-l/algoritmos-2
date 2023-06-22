


"(***)" ////// Comandos:

// Ejecucion directa:
➜     valgrind ./ejecutable <argumentos>
{Ejecutamos valgrind en el ejecutable con los argumentos}

// Reporte mas detallado:     /*Importante haber compilado con -g*/
➜     valgrind --leak-check=full ./ejecutable <argumentos>

// Ubucacion de los valores no inicializados:
➜     valgrind --track-origins=yes ./ejecutable <argumentos>

// Listas de errores detectados y suprimidos (flag -s)
➜     valgrind -s ./ejecutable <argumentos>   /*La flag -s se puede añadir a todos los codigos*/


//// Valgrind + GDB :  /* Acordarse de usar -g al compilar */

Pagina: https://valgrind.org/docs/manual/manual-core-adv.html

// Iniciar valgrind:   /* Se pueden añadir todas las banderas vistas anteriormente */
➜     valgrind --vgdb=yes --vgdb-error=0 ejecutable

El argumento "--vgdb=yes" habilita la integración con GDB, y "--vgdb-error=0" desactiva la finalización automática del programa después de que Valgrind haya terminado.

// En otro shell, iniciar GDB: 
➜     gdb programa

// Luego dé el siguiente comando a GDB: 
(gdb)     target remote | vgdb








"(***)" ////// Glosario:

// Info de Valgrind: 
valgrind ./ej ../input/example-unsorted.in 
==13692== Memcheck, a memory error detector
==13692== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==13692== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info

/*Esta sección proporciona información sobre Valgrind, incluida la versión y los detalles de derechos de autor.*/


// Blocks: 
Unidad de memoria que devuelven calloc, malloc... El tamaño del bloque lo definimos nosotros al llamarlo. 

// Stack: 
Aca se encuentran todas las variables que declaramos en el programa.
Es memoria estatica, se maneja sola.

// Heap:
Lugar donde va a estar la memoria que pedimos a traves de malloc, calloc... 
Es memoria dinamica, la manejamos nosotros. Esto significa que debemos pedirla y devolverla siempre!!
 
// Ubicación específica en la memoria del sistema:
Al hablar de una ubicación específica en la memoria del sistema la ubicamos como una dirección de memoria en formato hexadecimal como "0x...". Cada byte en la memoria tiene una dirección única que se puede representar en hexadecimal.

// ==xx...xx== at ...
indica de donde se origino el error.

// ==xx...xx== by ...
indica a donde se propago el error.








"(***)" //////  Seccion del resumen del uso de memoria realizado por el programa:

// Ejemplo de una ejecucion correcta:
==13692== Command: ./ej ../input/example-unsorted.in
==13692== 
length: 5
[ 0, 8, 3, -1, 2]
==13692== 
==13692== HEAP SUMMARY:
==13692==     in use at exit: 0 bytes in 0 blocks
==13692==   total heap usage: 9 allocs, 9 frees, 5,688 bytes allocated
==13692== 
==13692== All heap blocks were freed -- no leaks are possible
==13692== 
==13692== For lists of detected and suppressed errors, rerun with: -s
==13692== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)






"(*)" //// Error Stack overflow (Desbordamiento de pila)

Este mensaje de error indica que se produjo un desbordamiento de la pila (stack overflow) en el hilo #N del programa. Esto generalmente ocurre cuando el tamaño de la pila asignado al programa no es suficiente para acomodar todas las llamadas recursivas o variables locales almacenadas en la pila.

El desbordamiento de la pila aparece relacionado con una función FUNCION() en el archivo "ARCHIVO.c" en la línea M. Es posible que haya una recursión infinita o una llamada recursiva que no termine correctamente, lo que causa que se agote el espacio de la pila y resulte en un error de violación de segmento (SIGSEGV).

Si ese no es el problema (improbable pero posible), se puede intentar aumentar el tamaño de la pila del hilo principal utilizando la opción --main-stacksize al ejecutar Valgrind de la siguiente forma:

➜     valgrind --main-stacksize=<tamaño_en_bytes> ./readtree input/abb_example.in


// Ejemplo:
==73126== Stack overflow in thread #N: can't grow stack to 0x1ffe801000
==73126== 
==73126== Process terminating with default action of signal 11 (SIGSEGV)
==73126==  Access not within mapped region at address 0x1FFE801FF8
==73126== Stack overflow in thread #N: can't grow stack to 0x1ffe801000
==73126==    at 0x109363: FUNCION (ARCHIVO.c:M)
==73126==  If you believe this happened as a result of a stack
==73126==  overflow in your program's main thread (unlikely but
==73126==  possible), you can try to increase the size of the
==73126==  main thread stack using the --main-stacksize= flag.
==73126==  The main thread stack size used in this run was 8388608.

// Traduccion:
== 73126 == Desbordamiento de pila en el hilo #N: no se puede hacer crecer la pila a 0x1ffe801000 
== 73126 == 
== 73126 == Proceso que termina con acción predeterminada de la señal 11 (SIGSEGV) 
== 73126 == Acceso no dentro de la región mapeada en la dirección 0x1FFE801FF8 
== 73126 == Desbordamiento de pila en el hilo #N: no se puede hacer crecer la pila a 0x1ffe801000 
== 73126 == en 0x109363: FUNCION (ARCHIVO.c:M) 
== 73126 == Si crees que esto sucedió como resultado de una pila 
== 73126 == Desbordamiento en el subproceso principal de su programa (improbable pero 
== 73126 == posible), puede intentar aumentar el tamaño del 
== 73126 == pila de hilos principal usando la bandera --main-stacksize=. 
== 73126 == El tamaño de la pila de hilos principal utilizado en esta ejecución fue 8388608.








"(*)" //// HEAP SUMMARY:  /*resumen del uso de la memoria dinámica (heap)*/

// In use at exit (en uso al salir): 
Indica la cantidad de memoria que todavía está en uso al finalizar la ejecución del programa. En tu caso, se están utilizando 160 bytes en 10 bloques de memoria.


// Total heap usage (uso total de la memoria dinámica): 
Muestra el recuento total de asignaciones y liberaciones de memoria realizadas durante la ejecución del programa. Además, muestra la cantidad de bytes asignados en la memoria.


//b (n direct, m indirect) bytes in k blocks are definitely lost in loss record 10 of 10 (b bytes en k bloques están definitivamente perdidos en el registro de pérdida 10 de 10):
Esta línea especifica la cantidad de memoria perdida definitivamente en bloques que se consideran fugas de memoria. b bytes perdidos definitivamente, con n bytes asignados directamente y m bytes asignados indirectamente, en k bloques. Esta información se refiere a la categoría "Definitely lost" mencionada en "LEAK SUMMARY".






"(*)" //// LEAK SUMMARY:   /*resumen de las fugas de memoria detectadas durante la ejecución del programa*/

// Definitely lost:
Memoria que pedimos a la que accediamos a traves de un puntero P que pisamos antes de liberarlo o copiarlo. 


// Indirectly lost:
Indica la cantidad de memoria asignada dinámicamente que no se ha liberado, pero que aún tiene un puntero que apunta a ella. 


// Possibly lost:
Se refiere a la memoria que no se ha liberado y para la cual no hay ninguna referencia directa o indirecta en el programa. Sin embargo, esta categoría puede generar falsos positivos, lo que significa que Valgrind sospecha que se ha perdido la memoria, pero no puede confirmarlo de manera concluyente.


// Still reachable:
Se refiere a la memoria asignada dinámicamente que aún es accesible y que no ha sido liberada, pero que podría ser utilizada en el futuro. Es una categoría menos preocupante en comparación con las fugas definitivas o indirectas. 


// Suppressed:
Representa la cantidad de memoria que Valgrind ha decidido no informar debido a que se considera información irrelevante o no significativa para el análisis de fugas de memoria.


// Conditional jump or move depends on uninitialised value(s):
Este error indica que hay un salto condicional o movimiento que depende de valores no inicializados. Esto significa que estás utilizando una variable o valor que no ha sido correctamente inicializado antes de ser utilizado en una operación condicional o de salto.

Es probable que haya una variable o valor utilizado en una operación condicional en la funcion marcada luego de este error (la funcion en la linea con at) que no ha sido inicializado previamente. Esto puede conducir a un comportamiento impredecible del programa.

Muchas veces sucede por no usar calloc en vez de malloc.

* Para ver exactamente donde ocurre el error se debe usar la bandera --track-origins=yes y la linea donde esta este aparecera en el at abajo de "Uninitialised value was created by a heap allocation" --->


//  Uninitialised value was created by a heap allocation:           (--track-origins=yes)
El mensaje "Uninitialised value was created by a heap allocation" se refiere a una situación en la que se asigna memoria en el montón (heap) mediante una función como malloc, pero el valor asignado no se inicializa antes de su uso.

Cuando usas malloc para asignar memoria en el montón, obtienes un bloque de memoria que puede contener datos basura, es decir, datos que están presentes en esa ubicación de memoria pero no tienen un valor definido y pueden ser aleatorios. Si no inicializas explícitamente los datos asignados con valores conocidos, estarás trabajando con valores no inicializados, lo que puede provocar comportamientos inesperados y errores en tu programa.

Se puede corregir mediante la asignación explícita de valores, cambiando maloc por calloc o utilizando funciones como memset para establecer los valores iniciales del bloque de memoria asignado.


// Invalid read of size X:
Indica que estás intentando leer X bytes de una dirección de memoria a la que no tienes acceso válido. 

Puede ser causado por Desbordamiento de búfer, Liberación incorrecta de memoria,  Uso de punteros no válidos o Errores en la asignación de memoria dinámica.

Lo mas comun es que suceda cuando en un ciclo, el indice se pasa del limite de el arreglo o cuando ponemos primero en la guarda del ciclo un acceso a memoria antes que la condicion de que el indice debe ser menor al limite (en este caso se tratara de leer algo fuera del limite). 


// Invalid write of size X:
Indica que estás intentando escribir X bytes en una dirección de memoria a la que no tienes acceso válido.

Puede ser causado por Desbordamiento de búfer, Liberación incorrecta de memoria,  Uso de punteros no válidos o Errores en la asignación de memoria dinámica.

Lo mas comun es que suceda al no haberle reservado (con malloc, calloc...) el suficiente espacio a un arreglo por ejemplo y querer esbribir mas elementos de los que pediste para que pueda contener.


// Address 0x... is N bytes after a block of size X alloc'd:
Indica que estás accediendo a una dirección de memoria que está fuera de los límites de un bloque previamente asignado.

Significa que la dirección de memoria "0x..." se encuentra a una distancia de N bytes después de un bloque de memoria previamente asignado de tamaño X. En otras palabras, después de asignar un bloque de memoria de tamaño X, el programa utiliza esa dirección de memoria para acceder a otra ubicación en la memoria que está N bytes después del final del bloque asignado.

Este error se debe a desbordamientos de memoria o accesos incorrectos a la memoria. 

Puede ser causado por Desbordamiento de búfer, Liberación incorrecta de memoria,  Uso de punteros no válidos o Errores en la asignación de memoria dinámica.



// Glosario: 

"Desbordamiento de búfer": Si se asigna un bloque de memoria de tamaño X, pero posteriormente se escriben más datos de los esperados en ese bloque, se puede producir un desbordamiento de búfer. Esto puede resultar en que los datos adicionales se escriban en direcciones de memoria posteriores al bloque asignado, lo que daría lugar a la advertencia o error mencionado.

"Liberación incorrecta de memoria": Si se libera un bloque de memoria antes de tiempo, pero luego se intenta acceder a una dirección de memoria dentro de ese bloque, se puede generar la advertencia o error. Esto ocurre cuando el programa asume que el bloque de memoria aún está válido, pero ya ha sido liberado y posiblemente reutilizado para otros fines.

"Uso de punteros no válidos": Si se utilizan punteros que apuntan a direcciones de memoria inválidas o no asignadas, es posible que se produzcan errores como el mencionado. Esto puede suceder si un puntero no se inicializa correctamente, se desreferencia después de que el objeto al que apuntaba ha sido liberado o se realiza una aritmética de punteros incorrecta.

"Errores en la asignación de memoria dinámica": Si se produce un error en la asignación o liberación de memoria dinámica, como una asignación insuficiente o una liberación duplicada, puede provocar problemas de acceso a direcciones de memoria no válidas y generar este tipo de error.






"(*)" //// ERROR SUMMARY: /*resumen de los errores detectados durante la ejecución del programa*/

// n errors from m contexts: 
Indica que se han detectado un total de n errores en m contextos diferentes. Un contexto en Valgrind se refiere a una ubicación específica o una parte del programa donde se ha detectado un error. Estos errores pueden ser de diferentes tipos, como errores de uso de memoria, violaciones de acceso, etc.


// suppressed: n from m: 
Esta línea indica que se han suprimido n errores de m detectados porque se consideran irrelevantes o no críticos para el análisis. 

Siempre es recomendable revisar y analizar los errores suprimidos para asegurarse de que no se están ignorando problemas importantes. Se puede ejecutar Valgrind con opciones adicionales para mostrar detalles específicos sobre los errores suprimidos y las razones de la supresión.





"(***)" ////// Valgrind y KCachegrind:

➜     valgrind --tool=callgrind <ruta_del_ejecutable>
{Ejecuta el programa con Valgrind y genera los datos de perfilado}

Esto generará un archivo de datos de perfilado con extensión .callgrind en el directorio actual.

Luego abrimos la interfaz gráfica de KCachegrind. Alli seleccionamos "Abrir archivo" desde el menú "Archivo" o con el botón correspondiente en la barra de herramientas. Navegamos hasta el directorio donde se generó el archivo de datos de perfilado y seleccionamos el archivo con extensión .callgrind.


//Algunas de las vistas y características para analizar los datos de rendimiento del programa:

Gráfico de llamadas: Muestra la estructura de llamadas de funciones y el impacto en el rendimiento.
Vista de función: Proporciona detalles sobre el rendimiento de cada función.
Vista de código fuente: Muestra el código fuente junto con información de rendimiento.
Vista de caché: Proporciona información sobre los fallos de caché y el comportamiento del acceso a memoria.

Esto sirve para analizar y comprender el rendimiento del programa, identificar cuellos de botella y tomar decisiones de optimización.





