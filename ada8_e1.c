/* Programa: muestra un mensaje o frase cada x segundos */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//aqui declaracion de arreglo de frases


int main( int argc, char* argv[]  )
{
   int SLEEPTIME=10;
   int cont=0;

   for( ; ; ) {
       fprintf(stderr,"%s", "\007");
	   fprintf(stderr,"La frase del dia es: %d\n",cont);
  	   cont++;
      sleep(SLEEPTIME);
   }
  return 0; 
}
