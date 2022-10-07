/*Ejercicio1: Escribir un  programa que elija al azar un archivo de texto de un
 directorio y lo muestre.  
*/

//ej1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

char lista[100][50];
int conta=0;
int azar=0;

void mostrar(char *name){

 FILE *archivo;
 char buffer[2000];
 
 archivo = fopen(name,"r+b");
 fread(&buffer,2000,1,archivo);
 printf("%s\n",buffer);
 fclose(archivo);

}

static void listar(const char *path)
{
    DIR *dirp;
    struct dirent *dp;
    struct stat statbuf; 
     conta=0;

    if ((dirp = opendir(path)) == NULL) {
        printf("no se pudo abrir %s",path);
        return;
    }
    do { // cada llamada a readdir devuelve una entrada del directorio
        errno = 0;
     if ((dp = readdir(dirp)) != NULL) {     

     	 if (stat(dp->d_name, &statbuf) != -1) {     
	       if( ((statbuf.st_mode & S_IFDIR) != S_IFDIR )  && ( (statbuf.st_mode & S_IXUSR) != S_IXUSR  ) ){
	        // printf("%s \n",dp->d_name);  // nombre del archivo o directorio
             strcpy (lista[conta], dp->d_name);
             printf("%s \n",lista[conta]); 
             conta++;
  		  }
  	    }
       }
    } while (dp != NULL);
    
    //(void) closedir(dirp);
    closedir(dirp);

    if (errno != 0)
        perror("error al leer el directorio");
    
    azar = rand( )  % conta ;
    printf("\nSe eligio: %s \n\n",  lista[azar] );
    
     //abrir el archivo y mostrar su contenido
    mostrar(lista[azar]);
   
}


int main(int argc, char *argv[])
{
    int i;
	// listar el directorio pasado en arg
	srand( time(0) ); 
    switch(argc) {
	case 2:
        listar(argv[1]); // pasar el directorio
	   break;
	case 1:
        listar(".");    // usar el directorio actual
	  break;
	default:
	  printf("Usar: ej1 o ej1 path\n");
    }
    return (0);
}

