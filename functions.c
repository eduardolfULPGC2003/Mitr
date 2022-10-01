#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

#include "functions.h"

int Reemplazar(char *cadena1, char *cadena2, char *arch1, char *arch2) {
	int fd1, fd2, leidos;
	int pos_actual = 0;
	char caracter[1];
	if (strlen(cadena1)!=strlen(cadena2)){
		printf("Cadenas de diferente longitud. Abortando.\n");
		return -1;
	}
	if (strcmp(arch1, arch2)==0)
		fd2=open("intermedio", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	fd1=open(arch1,O_RDONLY);

   if (fd1==-1||fd2==-1){
      fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
      return -1;
   }

	 while (read(fd1, caracter, 1)!=0){
			if (caracter[0] == cadena1[0] && strlen(cadena1)==1){
				write(fd2, cadena2, 1);
				leidos++;
			}
			else if (caracter[0] == cadena1[0] && strlen(cadena1)!=1){
				pos_actual = leidos;
				for (int i=1; i<strlen(cadena1);i++){
					read(fd1, caracter, 1);
					if (caracter[0] != cadena1[i]){
						lseek(fd1, -i-1, SEEK_CUR);
						read(fd1, caracter, 1);
						write(fd2, caracter, 1);
						leidos++;
						break;
					}
					if (i==strlen(cadena1)-1 && caracter[0] == cadena1[i]){
						write(fd2, cadena2, strlen(cadena1));
						leidos += strlen(cadena1);
					}
				}
			}
			else {
				write(fd2, caracter, 1);
				leidos++;
			}
	 }

	 if (close(fd1)==-1 || close(fd2)==-1) {
      fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
      exit(-1);
   }

	 if (strcmp(arch1, arch2)==0) {
		rmdir(arch1);
		rename("intermedio", arch1);
	 }
	 return 1;
}




int Contar(char *cadena1, char *arch1) {
	int fd1, leidos;
	int pos_actual = 0;
	int contador = 0;
	char caracter[1];
	fd1=open(arch1,O_RDONLY);

   if (fd1==-1){
      fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
      return -1;
   }

	 while (read(fd1, caracter, 1)!=0){
			if (caracter[0] == cadena1[0] && strlen(cadena1)==1){contador++;}
			else if (caracter[0] == cadena1[0] && strlen(cadena1)!=1){
				pos_actual = leidos;
				for (int i=1; i<strlen(cadena1);i++){
					read(fd1, caracter, 1);
					if (caracter[0] != cadena1[i]){
						lseek(fd1, -i-1, SEEK_CUR);
						read(fd1, caracter, 1);
						leidos++;
						break;
					}
					if (i==strlen(cadena1)-1 && caracter[0] == cadena1[i]){
						leidos += strlen(cadena1);
						contador++;
					}
				}
			}
			else {
				leidos++;
			}
	 }

	 if (close(fd1)==-1) {
      fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
      exit(-1);
   }
	 printf("Se han encontrado %d \"%s\"", contador, cadena1);
	 return 1;
}





int Borrar(char *cadena1, char *arch1, char *arch2) {
	int fd1, fd2, leidos;
	int pos_actual = 0;
	char caracter[1];
	if (strcmp(arch1, arch2)==0)
		fd2=open("intermedio", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	fd1=open(arch1,O_RDONLY);

   if (fd1==-1||fd2==-1){
      fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
      return -1;
   }

	 while (read(fd1, caracter, 1)!=0){
			if (caracter[0] == cadena1[0] && strlen(cadena1)==1){
				leidos++;
			}
			else if (caracter[0] == cadena1[0] && strlen(cadena1)!=1){
				pos_actual = leidos;
				for (int i=1; i<strlen(cadena1);i++){
					read(fd1, caracter, 1);
					if (caracter[0] != cadena1[i]){
						lseek(fd1, -i-1, SEEK_CUR);
						read(fd1, caracter, 1);
						write(fd2, caracter, 1);
						leidos++;
						break;
					}
					if (i==strlen(cadena1)-1 && caracter[0] == cadena1[i]){
						printf("Dentro");
						leidos += strlen(cadena1);
					}
				}
			}
			else {
				write(fd2, caracter, 1);
				leidos++;
			}
	 }

	 if (close(fd1)==-1 || close(fd2)==-1) {
      fprintf(stderr,"error %d: %s\n",errno,strerror(errno));
      exit(-1);
   }

	 if (strcmp(arch1, arch2)==0) {
		rmdir(arch1);
		rename("intermedio", arch1);
	 }
	 return 1;
}
