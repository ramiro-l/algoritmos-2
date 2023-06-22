

//// SIGSEGV (Segmentation fault)

//Ejemplo: 

Program received signal SIGSEGV, Segmentation fault.
0x00005555555552e7 in FUNCION (tree=<error reading variable: No se puede acceder a la memoria en la dirección X>)

// Posibles causas: 
si (X == 0x0) => se esta intentando acceder a NULL
si (X != 0x0) => 
	1. Es posible que haya una recursión infinita o una llamada recursiva que no termine correctamente, lo que causa que se agote el espacio de la pila y resulte en un error de violación de segmento (SIGSEGV).
	2. Se le esta pasando a la funcion un puntero p no valido (no inicializado, sin memoria reservada o que apunta a un lugar incorrecto)
	3. ...

            
            
            
            
            
            
            
            
            
