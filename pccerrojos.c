#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#define Longitud 5
#define Cantidad 20
int Caja[Longitud];
unsigned Primero = 0;
unsigned Ultimo = 0;
unsigned Numero = 0;
pthread_mutex_t cerrojo = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t huecos = PTHREAD_COND_INITIALIZER;
pthread_cond_t elementos = PTHREAD_COND_INITIALIZER;
/* Pone en entero en la cola, deteniéndose si no cabe */
void Pon(int X) {
pthread_mutex_lock (&cerrojo);
while (Numero == Longitud)
pthread_cond_wait(&huecos, &cerrojo);
Caja[Ultimo] = X;
Ultimo = (Ultimo + 1) % Longitud;
Numero++;
pthread_cond_signal(&elementos);
pthread_mutex_unlock(&cerrojo);
return;
}
/* Toma un entero de la cola, deteniéndose si no hay */
void Toma(int *pX) {
pthread_mutex_lock (&cerrojo);
while (Numero == 0)
 pthread_cond_wait(&elementos, &cerrojo);
 *pX = Caja[Primero];
 Primero = (Primero + 1) % Longitud;
 Numero--;
 pthread_cond_signal(&huecos);
 pthread_mutex_unlock(&cerrojo);
return;
}
/* Proceso que produce enteros y los encola */
void *Productor (void *pId) {
unsigned Id = *(unsigned*)pId;
unsigned long Periodo = Id * 1000;
int i;
for (i = 1; i <= Cantidad; i++) {
  Pon(i + Id);
  printf("---- Productor %6d produce %6d\n", Id, i+Id);
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
int main(void) {
pthread_t productorid;
pthread_t consumidorid;
unsigned Id_Productor=1000;
unsigned Id_Consumidor=5000;
/* crear las hebras */
pthread_create(&productorid, NULL, Productor, &Id_Productor);
pthread_create(&consumidorid, NULL, Consumidor, &Id_Consumidor);
/* esperar a que acaben las hebras */
pthread_join(productorid, NULL);
pthread_join(consumidorid, NULL);
exit(0);
}
