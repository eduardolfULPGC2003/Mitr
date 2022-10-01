#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

#include "functions.h"




int main(int argc, char **argv)
{
   if (argc>1 && strcmp(argv[1], "-d")==0){
		if (argc!=5) printf("5 argumentos esperados, recibidos %d. Debería ser: ./mitr -d <cadena a eliminar> <archivo1> <archivo2>.\n", argc);
		else Borrar(argv[2], argv[3], argv[4]);
	 }
	 else if (argc>1 && strcmp(argv[1], "-i")==0){
		if (argc!=4) printf("4 argumentos esperados, recibidos %d. Debería ser: ./mitr -i <cadena a buscar> <archivo>.\n", argc);
		else Contar(argv[2], argv[3]);
	 }
	 else if (argc==5){Reemplazar(argv[1], argv[2], argv[3], argv[4]);}
	 else {
	 printf("No has introducido ninguna de las opciones permitidas. Las opciones permitidas son:\n");
	 printf("1.- ./mitr -d <cadena a eliminar> <archivo1> <archivo2>.\n");
	 printf("2.- ./mitr -i <cadena a buscar> <archivo>.\n");
	 printf("3.- ./mitr <cadena1> <cadena2> <archivo1> <archiv2>.\n");
	 printf("Abortando.\n");
   exit(0);
	}
}


