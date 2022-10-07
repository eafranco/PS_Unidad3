/* Programa: frases.c*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define SLEEPTIME 10

int main(void)
{
  int mailfd;
	int cont=0;

   for( ; ; ) {
      cont++;
      fprintf(stderr,"%s", "\007");
		  
		  fprintf(stderr,"Enviando mensajes %d\n",cont);
        
      sleep(SLEEPTIME);
   }
  return 0; 

}
