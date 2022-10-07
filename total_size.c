#include <dirent.h>#include <errno.h>#include <stdio.h>
#include <stdlib.h>#include <string.h>#include <sys/types.h>#include <sys/stat.h>
//funcion que regresa el tama–o de un archivo
long int size_file( char *entrada){	struct stat statbuf; 		if (stat(entrada, &statbuf) == -1) {		fprintf(stderr, "No se pudo usar stat sobre el archivo %s: %s\n",			entrada, strerror(errno));		return 0;	}	if ( ! (statbuf.st_mode & S_IFDIR) ) {  // determinar si es un directorio		return (long int) statbuf.st_size;	} 
 return 0;	}

 void listar(const char *path){	DIR *dirp;
	long int size=0, tsize=0;	struct dirent *dp;	if ((dirp = opendir(path)) == NULL) {		printf("no se pudo abrir %s",path);		return;	}	do { // cada llamada a readdir devuelve una entrada del directorio		errno = 0;		if ((dp = readdir(dirp)) != NULL) {
			size=size_file(dp->d_name);
			tsize=tsize+size;			printf("%-25s   %d  %d \n", dp->d_name, dp->d_ino, size);
			//printf("%s %d \n", dp->d_name, dp->d_ino);
			//printf("nada\n");
		}	} while (dp != NULL);
	
	printf("\nTotal de bytes ocupados: %ld\n",tsize);
		(void) closedir(dirp);	if (errno != 0)		perror("error al leer el directorio");}int main(int argc, char *argv[]){	// listar el directorio pasado en arg	switch(argc) {	case 2:		listar(argv[1]); // pasar el directorio		break;	case 1:		listar(".");      // pasar directorio actual		break;	default:		printf("Usar: myls o myls path\n");	}	return (0);}