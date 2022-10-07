// pcsem.c: uso de semaforos
#define _REENTRANT
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define Longitud 5
#define Cantidad 20
int Caja[Longitud];
unsigned Primero = 0;
unsigned Ultimo = 0;
sem_t hayelementos;
sem_t hayhuecos;
sem_t cerrojo;
/* Pone en entero en la cola, deteniéndose si no cabe */
void Pon(int X) {
sem_wait(&hayhuecos);
sem_wait(&cerrojo);
Caja[Ultimo] = X;
Ultimo = (Ultimo + 1) % Longitud;
sem_post(&cerrojo);
sem_post(&hayelementos);
return;
}
/* Toma un entero de la cola, deteniéndose si no hay */
void Toma(int *pX) {
sem_wait(&hayelementos);
sem_wait(&cerrojo);
*pX = Caja[Primero];
Primero = (Primero + 1) % Longitud;
sem_post(&cerrojo);
sem_post(&hayhuecos);
return;
}
/* Proceso que produce enteros y los encola */
void *Productor (void *pId) {
unsigned Id = *(unsigned*)pId;
unsigned long Periodo = Id * 1000;
int i;
for (i = 1; i <= Cantidad; i++) {
Pon(i + Id);
printf("---- Productor %6d produce %6d\n",
Id, i+Id);
usleep(Periodo);
}
return NULL;
}
/* Proceso que consume enteros */
void *Consumidor(void *pId) {
unsigned Id = *(unsigned*)pId;
unsigned long Periodo = Id * 1000;
int Dato;
int j;
for (j = 1; j <= Cantidad; j++) {
Toma(&Dato);
printf("**** Consumidor %6d consume %6d\n", Id, Dato);
usleep(Periodo);
}
return NULL;
}
