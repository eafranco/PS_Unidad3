// exec3.c: implementa el comando system
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main (int argc, char *argv[])
{
pid_t childpid;

system(argv[1]);  //ejecuta un comando en el shell system("ls")

if ((childpid =fork()) ==-1)
{
   perror("Error al crear el hijo");
   exit(1);
}
else if (childpid ==0)
{
   printf("Soy el hijo y voy a ejecutar el comando %s/n",argv[1]);
  
   //esta es la llamada que se realiza con system()

if (execl("/bin/sh", "sh", "-c", argv[1], (char *) NULL) < 0 )
{
  perror("Error al ejecutar el comando");
  exit (1);
}
}
else
{
   int status;
   waitpid(childpid , &status, 0);
   printf("Soy el padre y termino\n");
   exit(0);
}
}