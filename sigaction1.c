//sigaction1.c  muestra la invocacion de un manejador al recibirse una señal
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void manejador1(int signum){
 // acciones si se captura señal
 printf("He capturado la señal ctrl-c\n");
 puts("Quieres continuar?: ");
 char sn=getc(stdin); //leer caracter desde stdin	
 //fflush(stdin); // limpiar buffer  	
	if(sn=='n' || sn=='N')
	{
	  printf("Proceso interrumpido por el usuario");
	exit(0);	
	}
	else
	 printf("Continuar hasta que expire mi tiempo...\n");
}

int main() {
struct sigaction sa;
sa.sa_handler = manejador1;  //para llamar a una funcion
//sa.sa_handler = SIG_IGN;  //para ignorar la señal
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_RESTART;
if( sigaction(SIGINT, &sa, NULL) ==-1) 
  perror("Error al tratar la señal\n");
printf("Para interrumpir el proceso ctrl-c\n");
alarm(25);
for(;;){ // pensando...

 printf("dentro del for\n");
 sleep(2);
}
printf("Continuamos con el proceso\n");  
return 0;
}

