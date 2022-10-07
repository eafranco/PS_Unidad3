//popen2.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//popen2.c:  ejecuta un comando y su salida la muestra en orden inverso
int main()
{

  char linea[256];
  FILE * fp;
  int i,nc;


 /* Abro un pipe de lectura para leer la salida del
    comando comando ls -l */

 fp = popen("ls -l","r");

 fgets(linea,256,fp); 
 while ( !feof(fp) )
   {
   nc = strlen(linea);
   // Muestro la línea alreves
   for (i= nc -1; i > 0; i--)
     {
     putchar(linea[i]);
     }
   fgets(linea,256,fp); 
   }

 /* Cierro el pipe  */
 pclose(fp);
 exit(0);
}
