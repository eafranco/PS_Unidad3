// exec/pipeline_reto.c: conecta tres procesos 
// y redirige las salidas y entradas estandar 
// debe hacer lo mismo que la orden:
//  awk -F: '{print $5}' /etc/passwd |grep r|sort
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void productor (void)
{
  execlp ("awk", "awk", "-F:", "{print $5}", "/etc/passwd", NULL);
  perror ("execlp");
  exit (1);
}

void consumidor (void)
{
  execlp ("grep","grep", "r", NULL);
  perror ("execlp");
  exit (1);
}

void consumidor2 (void)
{
  execlp ("sort", "sort", NULL);
  perror ("execlp");
  exit (1);
}

int main (void)
{
  int pid, pid2, tubo[2], tubo2[2];
  pipe (tubo);
  if ((pid = fork ()) == 0)
    {
      close(tubo[0]);
      dup2(tubo[1], 1); // redirige su salida a salida estandar
      close(tubo[1]);
      productor();
    }
  else
    {
      pipe(tubo2);
   if((pid2 = fork ()) == 0)
	{

	  close(tubo[1]);
	  dup2(tubo[0], 0); // redirige su entrada a entrada estandar
	  close(tubo[0]);
	  close(tubo2[0]);
	  dup2(tubo2[1],1); // redirige su salida a salida estandar de tubo2
	  close(tubo2[1]); 
	  consumidor();
	}
      else
	{
	 close(tubo[0]);  // NO olvidar cerrar cualquier recurso abierto
	 close(tubo[1]);
	 close (tubo2[1]);
	  dup2 (tubo2[0],0); // redirige a entrada estandar
	  close (tubo2[0]);
	  consumidor2(); 
	}
      
    }
}
