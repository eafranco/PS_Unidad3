/* mytree.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

static void listar(const char *path, int nivel)
{
    DIR *dirp;
    struct dirent *dp;
    struct stat statbuf; 
    int it=0; 

    if ((dirp = opendir(path)) == NULL) {
        printf("no se pudo abrir %s",path);
        return;
    }
    do { // cada llamada a readdir devuelve una entrada del directorio
        errno = 0;
     if ((dp = readdir(dirp)) != NULL) {     

     	 if (stat(dp->d_name, &statbuf) != -1) {     
	       if( ((statbuf.st_mode & S_IFDIR) != S_IFDIR )  && ( (statbuf.st_mode & S_IXUSR) != S_IXUSR  ) ){
	         
             for(it=0; it<nivel; it++)
                printf("\t");
             printf("%s \n", dp->d_name); 

  		  }
  	    }
       }
    } while (dp != NULL);

    (void) closedir(dirp);
    if (errno != 0)
        perror("error al leer el directorio");
}


int main(int argc, char *argv[])
{
    int i;
	// listar el directorio pasado en arg
    switch(argc) {
	case 2:
        listar(argv[1], 0); // pasar el directorio
	   break;
	case 1:
  	  listar(".", 0);      // pasar directorio actual
	  break;
	default:
	  printf("Usar: mytree o mytree path\n");
    }
    return (0);
}

