//alarma1.c
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int main (void)
{
alarm(5);
printf("Espero 5 segundos para terminar...\n");
alarm(10);
printf("no mejor 2 segundos ...\n");
for(;;){ 
  printf(".");
}
printf("No creo llegar hasta aqui...\n");
return 0;
}
