//envio de señales con la llamada a kill
// ¿quién mata a quien??
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
int main (void)
{
int pid;
pid = fork();
switch (pid)
{
 case 1: perror ("No se ha podido crear el hijo"); 
    break;
 case 0: printf("Soy el hijo, mi PID es %d y mi PPID es %d\n",
     getpid(), getppid());
    // caso siniestro, el hijo mata a su padre
     if( kill(getppid(), SIGTERM) == -1)     //  kill envía la señal al proceso.
		 perror("Error en kill");
    break;
 default: printf ("Soy el padre, mi PID es %d y el PID de mi hijo es %d\n", getpid(), pid );
   printf("%d",kill(pid,SIGTERM) );
	 // el padre mata al hijo
}
return 0;
}
