// pipe/ppipe3.c : 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void productor(int esc) {
  int i;
  for (i=1; i<=10; i++) {
    write(esc, &i, sizeof i); 
	printf("Productor escribio el valor %d\n", i);
    sleep(1);
 }
exit(0);
}
void consumidor(int lec) {
   int leidos, i;
   while ((leidos = read(lec, &i, sizeof i)) > 0)
       printf("Consumidor 1 recibio %d\n", 
i);
   exit(0);
}

void consumidor2(int lec) {
   int leidos, i;
   while ((leidos = read(lec, &i, sizeof i)) > 0)
	{   
      printf("Consumidor 2 recibio %d\n", i);
	  sleep(4); // un consumidor mas lento
	}   
   exit(0);
}

int main(void) {
int pid, pid2, tubo[2];
pipe(tubo);  // crea la tuberia
if ((pid= fork())==0) {
   close(tubo[1]); // cierra estremo de escritura
   consumidor(tubo[0]);
 }
else {
	// crear un tercer proceso que lee del pipe
	if ((pid2 = fork())==0) {
      close(tubo[1]); // cierra estremo de escritura
      consumidor2(tubo[0]);
    }
	else 
	{
      close(tubo[0]); // cierra estremo de lectura
      productor(tubo[1]);
	}
 }
}
