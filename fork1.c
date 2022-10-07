//fork1.c: creación de procesos (hilos) con fork
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main (void)
{
int pid;
pid = fork(); //CREA IMAGEN DE HIJO
switch (pid)
{
 case 1: perror ("No se ha podido crear el hijo"); 
    break;
 case 0: printf("Soy el hijo, mi PID es %d y mi PPID es %d\n",
     getpid(), getppid());
     sleep(40);
     //pause();
    break;
 default: printf ("Soy el padre, mi PID es %d y el PID de mi hijo es %d\n", getpid(), pid );
    sleep(40);
   printf("%d",kill(pid,SIGTERM) );
}

return 0;
}
