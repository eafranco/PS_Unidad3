//ejemplo signal2.c con funcion signal()

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>


static void manejador1(int signum){
// acciones si se captura señal
if(signum==SIGINT){
printf("He capturado la seÃ±al ctrl-c\n");
puts("Quieres continuar?: ");
char sn[20];
fflush(stdin); // limpiar buffer 
gets(sn); //leer caracter desde stdin 
//fflush(stdin); // limpiar buffer 
if(sn[0]=='n' || sn[0]=='N')
{
printf("Proceso interrumpido por el usuario");
exit(0); 
}
else
{ printf("Continuar hasta que expire mi tiempo...\n");
if( signal(SIGINT, manejador1) ) // necesario volver a especificar señal a capturar
perror("Error al tratar la señal\n");
}
}else { fprintf(stderr,"Error: esperado=%d, recibido=%d \n", SIGINT, signal); 
	
}
 
}

int main() { 
int n, i=1,j=0; 
 if( signal(SIGINT, manejador1) )  
    perror("Error al tratar la senial\n"); 
 printf("Para interrumpir el proceso ctrl-c\n");  
 for(i=1;i<5000; i++){

  // pensando...  
 	for(j=0; j<35000; j++) 
 		printf(""); 
      }
 	 printf("Fin de proceso\n");  
 	system("pause"); 
 	return 0;
  } 
