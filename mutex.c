#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 

#define MAX 10  // numeros a producir

pthread_mutex_t el_mutex;
pthread_cond_t condc, condp;
int bufer=0;   /* recurso compartido */

void *productor( void *ptr) {
 int i;
 for(i=1; i<=MAX; i++)
 {
	 pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al bufer */ 
	 while(bufer!=0 ) pthread_cond_wait(&condp, &el_mutex); 
	    /* en cond_wait necesita que ambos sean verdadero para continuar
	      si no, se desbloquea el mutex y espera*/ 
	 bufer=i;			/* coloca elemento en el bufer */
	 printf("Produce. %d \n",bufer);
	 pthread_cond_signal(&condc);  /*despierta al consumidor */
	 pthread_mutex_unlock(&el_mutex); /*libera el recurso */ 
  }
 pthread_exit(0);  
 } 

void *consumidor( void *ptr) {
  // escribir el código que falta
  int i;
 for(i=1; i<=MAX; i++)
 {
	 pthread_mutex_lock(&el_mutex); /* obtiene acceso exclusivo al bufer */ 
	 while(bufer==0 ) pthread_cond_wait(&condc, &el_mutex);
			/* lee elemento del bufer */
	 printf("Consume. %d \n",bufer);
	 bufer=0;
	 pthread_cond_signal(&condp);  /*despierta al productor */
	 pthread_mutex_unlock(&el_mutex); /*libera el recurso */ 
  }
 pthread_exit(0);  
}

int main() {
 pthread_t pro, con;
 pthread_mutex_init(&el_mutex,0);
 pthread_cond_init(&condp,0);
 pthread_cond_init(&condc,0);
  pthread_create(&con, 0, consumidor, 0);
  printf("Inicio el consumidor\n");
  sleep(5);
  pthread_create(&pro, 0, productor, 0);


 pthread_join(pro,0);
 pthread_join(con,0);
 pthread_cond_destroy(&condc);
 pthread_cond_destroy(&condp);
 pthread_mutex_destroy(&el_mutex);
 return 0;
}
