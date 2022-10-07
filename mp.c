#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void main (int argc, char *argv[])
{
pid_t childpid;
if ((childpid =fork()) ==-1)
{
   perror("Error al crear el hijo");
   exit(1);
}

else if (childpid ==0)
{
printf("Soy el hijo y voy a ejecutar el comando %s\n",argv[1]);
 if (execvp(argv[1], &argv[1]) <0)
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

