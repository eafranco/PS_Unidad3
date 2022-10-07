//wait1.c: creación de procesos (hilos) con fork
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main (void)
{
pid_t pid,childid;
pid = fork();
switch (pid)
{
 case 1: perror ("No se ha podido crear el hijo"); 
    break;
 case 0: printf("Soy el hijo, mi PID es %d y mi PPID es %d\n",
     getpid(), getppid());
     int i=0;
     for(i=0; i<100000; i++) { }
     	sleep(40);
    break;
 default: printf ("Soy el padre, mi PID es %d y espero a mi hijo con PID  %d\n", getpid(),pid );
     if( (childid=wait(0))==-1)
       printf("no pudo esperar al hijo");
    else
       printf("mi hijo con pid %d ha muerto",childid ); 

}

return 0;
}
