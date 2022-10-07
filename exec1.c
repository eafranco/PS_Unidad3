// exec1.c: usa execl para sustituir la imagen de un programa
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main (void)
{
pid_t childpid;
if ((childpid =fork()) ==-1)
{
  perror("Error al crear el hijo");
   exit(1);
}
else if (childpid ==0)
{
  printf("Soy el hijo y voy a ejecutar ls -l\n");
   if (execl("/bin/ls", "ls", "-l", NULL) <0)
    {
      perror("Error al ejecutar ls\n");
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
