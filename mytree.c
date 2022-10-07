/*
mytree.c: 
Programa que lista el arbol de directorios dada la raiz del mismo
de forma recursiva, omitiendo aquellos que no lo sean 
o que sean  directorio especiales(., ..)
*/


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
char nruta[250]="";

if ((dirp = opendir(path)) == NULL) {
    printf("no se pudo abrir %s",path);
  return;
}
do { // cada llamada a readdir devuelve una entrada del directorio
errno = 0;
if ((dp = readdir(dirp)) != NULL) {

  if( strcmp( dp->d_name, "." )==0 || strcmp( dp->d_name, ".." )==0 || strcmp( dp->d_name, ".DS_Store" )==0 )
  continue;

 char fp[250]="";
 strcpy( fp, path );
 strcat( fp, "/" );
 strcat( fp, dp->d_name );


if (stat(fp, &statbuf) != -1) {

if ( (statbuf.st_mode & S_IFDIR) == S_IFDIR ){
 
 for(int it=0; it<nivel; it++)  //incrementa espacios
   printf("  ");

  printf("%s\n",fp);  //imprime directorio

 char nruta[250]="";
 strcpy( nruta, path );
 strcat( nruta, "/" );
 strcat( nruta, dp->d_name);

 listar( nruta , nivel+1);  //llamado recursivo con nuevo directorio
 
 }

}
else{
  printf("No leyo statbuf\n");
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
listar(argv[1], 1); // pasar el directorio
break;
case 1:
listar(".", 1); // pasar directorio actual
break;
default:
printf("Usar: mytree o mytree path\n");
}
return (0);
}
