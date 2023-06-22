////OBS:
-g es una opcion de depuración que permite hacer un seguimiento del proceso del codigo. 

//// Proceso de uso de GDB:
(Complilamos normalmente agregando -g)

$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -c main.c
{compila main.c, crea objeto main.o}
$     gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -o ejecutable main.o
{crea el ejectable en miprograma}

//Compilado en una linea:
$     gcc -Wall  -Werror -Wextra -pedantic -std=c99 -g -o ejecutable main.c 
// si hacemos esto no podremos comprobar simbolos de debuggin

//compilado rapido:
$     gcc -Wall  -Werror -Wextra -pedantic -std=c99 -g -o ej *.c *.h
// si hacemos esto no podremos comprobar simbolos de debuggin

/*
Para saber si un programa compilado o un archivo.o tiene símbolos de debugging
podemos ejecutar: “objdump --syms <ejecutable o archivo.o>| grep debug”. Si la salida del
comando es vacía, no contiene símbolos de debugging, mientras que si muestra una
tabla tendrá símbolos de debugging.
*/

$     objdump --syms main.o librerias.o| grep debug
{Comprobamos símbolos de debugging}



//// Argumentos:

/* Opcion 1: Ejecutamos el programa siempre con argumentos fijos. Estructura: “gdb --args ./<nombre_ejecutable> <args>” */
//Ejemplo 1:    
$     gdb --args ./ejecutable argumentos.in       
{Ejecutamos el programa con los argumentos del archivo argumentos.in}


/*
Opcion 2: Ejecutamos el programa con argumentos variables (decidimos los argumentos dentro de gdb).
Estructura: “gdb ./<nombre_ejectuable>” y dentro de gdb al comenzar la ejecución hacemos: “run <args>” 
*/
//Ejemplo 2:    
$     	gdb ./ejecutable
{Ejecutamos el programa}
$     run argumentos.in   
{Corremos el programa con los argumentos del archivo argumentos.in}



//// Ayuda
$     help <comando>
{Esto nos mostrará la ayuda detallada de dicho comando.}
Links:  https://www.sourceware.org/gdb/
	https://www.sourceware.org/gdb/documentation/



//// Vista general a comanos principales:   (no importa orden mas que el de r y q)
$     l                 (list)
{imprime código}
$     b <numero_linea>  (break)
{poner un breakpoint en la línea <numero_linea>}
$     watch <var>
{poner un watchpoint en la variable <var>}
$     display <var>
{imprimir el valor de la variable <var> cada vez que para la ejecución}

$     r                 (run)
{empezar ejecución del programa}
$     c                 (continue)
{seguir ejecutando hasta el próximo breakpoint/watchpoint}
$     s                 (step)
{ejecutar una línea de código}
$     n                 (next)
{ejecutar una línea de código (sin entrar a funciones)}
$     w                 (where)
{Dice en qué función, línea y archivo estoy}
$     p <var>           (print)
{imprimir el valor de la variable <var>}
$     q o CTRL+D        (quit)
{Salimos de gdb}
 



////////  Breakpoints y Watchpoints

//// Breakpoints (Puntos de detención):
Breakpoints: Frenan en un punto especíﬁco del código. 

/* 
Si no ponemos "<archivo.c> :", gdb interpretará que es en el archivo donde se encuentra el main.
*/

...
$     break <archivo.c> : <nombre_de_funcion>
{El programa se detiene al llegar a la funcion <nombre_de_funcion>}
...
$     break <archivo.c>: <numero_linea>
{El programa se detiene al llegar a la linea <numero_linea>}
...
$     b <archivo.c> : <numero_linea> if (<condicion>)
{El programa se detiene al llegar a la linea <numero_linea> si se cumple la condicion <condicion>}



//// Watchpoints (Puntos de observacion):
Watchpoints: Frenan cada vez que se modiﬁca el valor de una variable. 

$     watch <var>
{establece un punto de detención cada vez que la variable var sea modiﬁcada}

//// Controlar el ﬂujo de ejecución con Breakpoints y Watchpoints: 

...
$     info breakpoints/watchpoints
{Consultar los breakpoints/watchpoints deﬁnidos}
...
$     enable <breakpoint/watchpoints_number>
{Habilitar un breakpoint/watchpoints}
...
$     disable <breakpoint/watchpoints_number>
{Deshabilitar un breakpoint/watchpoints}
...
$     delete <breakpoint/watchpoints_number>
{Borrar un breakpoint/watchpoints}
...

/*Los comandos habilitar, deshabilitar y borrar sin argumentos habilitarán,
deshabilitarán o borrarán todos los breakpoints/watchpoints según corresponda. */






//////// Controlar el ﬂujo de ejecución:
Una vez que hemos establecido nuestros watchpoints y/o breakpoint procedemos la ejecución con el comando run. Cada vez que el código pase por algúno, la ejecución se detendrá y podremos controlar manualmente el ﬂujo de ejecución con los comandos:


...
$     next
{Ejecuta la siguiente instrucción}
$     step
{Igual que next pero permite “entrar” dentro de una función}
$     ﬁnish
{ejecuta hasta ﬁnalizar la función actual}
$     continue
{Sigue el ﬂujo de ejecución hasta el próximo breakpoint/watchpoints}
...

//// ¿Donde estoy?

...
$     where
{Dice en qué función, línea y archivo estoy}
$     list <n>
{Imprime 10 líneas de código centradas en la línea n}
$     list -
{Imprime las 10 líneas anteriores}
$     list <nombre_función>
{Imprime 10 líneas centradas en la función seleccionada}
...


//// Consultar el estado de las variables:

...
$     ptype <var>
{imprime el tipo de la variable var}
$     print <format> <var or expr>
{imprime el contenido de la variable var con el formato deﬁnido en format. Si no ponemos formato, usará uno predeﬁnido}
$     display <var>
{imprimir el valor de la variable <var> cada vez que para la ejecución}
...

//// Cambiar el valor de las variables:

$     set <var> = <valor>
{Cambiamos el valor de <var> por <valor>}


//// Para moverse por la pila de ejecución:
Cada vez que llamamos a una función en el código la función padre queda
en stand by y se agrega a la pila la función llamada. Gdb permite consultar la pila de
ejecución y desplazarnos por ella.


$     backtrace
{imprime el estado de la pila de ejecución}
$     up
{sube un nivel en la pila de ejecución}
$     down
{baja un nivel en la pila de ejecución}
$     frame 
{retorna en que nivel de la pila ejecución estoy}
$     frame <n>
{avanza hasta el nivel n de la pila de ejecución}




$     
{}
$     
{}
$     
{}
$     
{}
$     
{}
