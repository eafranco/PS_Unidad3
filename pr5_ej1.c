/* myls.c: lista el directorio pasado como argumento,  si no se da el argumento, lista el directorio actual */
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

static void listar(const char *path)
{
    DIR *dirp;
    char namef[200][50];
    int x=0,nf=0;
    struct dirent *dp;
    srand(time(NULL));
    
    
    if ((dirp = opendir(path)) == NULL) {
        printf("no se pudo abrir %s",path);
        return;
    }
    do { // cada llamada a readdir devuelve una entrada del directorio
        errno = 0;
     if ((dp = readdir(dirp)) != NULL) {          
	     printf("%s \n",dp->d_name);  // nombre del archivo o directorio
	     strcpy(namef[nf],dp->d_name);
	     nf++;
        }
    } while (dp != NULL);
    (void) closedir(dirp);
    if (errno != 0)
        perror("error al leer el directorio");
    else {
    //desplegar un archivo del directorio al azar
    x=rand()%nf;
    printf("Indice: %d\n",x);
    printf("Archivo seleccionado: %s \n",namef[x]);
    int ret;
    ret = execlp ("cat", "cat", namef[x] , (char *)0);
    
    }    
        
}

int main(int argc, char *argv[])
{
    int i;
	// listar el directorio pasado en arg
    switch(argc) {
	case 2:
        	   listar(argv[1]); // pasar el directorio
	   break;
	case 1:
  	  listar(".");      // pasar directorio actual
	  break;
	default:
	  printf("Usar: myls o myls path\n");
    }
    return (0);
}

