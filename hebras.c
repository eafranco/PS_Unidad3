//Programa: hebras.c

#define _REENTRANT 
/* Aseguro que sólo llamo a
 rutinas reentrantes */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define MAXHEBRAS 100
char** argumentos;

void *escribe(void *idp) {
int i, salida;
char c;
int id = *(int *)idp;
if ((salida = open(argumentos[id], O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0) {
  fprintf(stderr, "Error al abrir %s\n", argumentos[id]);
  pthread_exit("mal");
}
for (i=0; i<20; i++) {
   sleep(id);
   c= 'A'+id-1;
   write(salida, &c, 1);
}
 pthread_exit("bien");
}

int main(int argc, char* argv[]) {
int i;
pthread_t hebra[MAXHEBRAS]; /* Identificador de hebra */
int id[MAXHEBRAS]; /* Parámetro de la hebra (para que no varíe) */
char *estado;
argumentos= argv;
for (i=1; i<argc; i++) {
id[i-1] = i;
if (pthread_create(&hebra[i-1], NULL, escribe, &id[i-1]) != 0) {
  fprintf(stderr, "Error al crear hebra\n");
   exit(1);
}
}
for (i=1; i<argc; i++) {
  pthread_join(hebra[i-1], (void**)&estado);
   printf("Terminada %s la hebra %d\n", estado, i);
}
exit(0);
}
