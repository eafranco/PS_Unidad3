#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

#define BLKSIZE  1024

//prototipos de funciones
void installusrhandlers();
void usr1handler(int s);
void usr2handler(int s);
void* do_lee(void* commfd);
void* do_escribe(void* commfd);



void usr1handler(int s)
{
   fprintf(stderr, "SIGUSR1 signal caught\n");
}
 
void usr2handler(int s)
{
   fprintf(stderr, "SIGUSR2 signal caught\n");
}
 
 void ctrl_handler(int s)
{ 
   char buf[50];
   int bytesread;
   //printf("\nSe capturo Ctrl-C \n");
   write(STDOUT_FILENO,"\nSe capturo Ctrl-C \n",20);
  // reinstalando manejadores
   //installusrhandlers();
   //printf("1) Regresar al chat \n2) Terminar procesos\n : ");
   write(STDOUT_FILENO, "1) Regresar al chat \n2) Terminar procesos\n : ", 45); 
  //int sn;
   //scanf(" %2d ",&sn); //leer caracter desde stdin 
   bytesread = read(STDIN_FILENO, buf, 10); 
  // printf("lei %d ", bytesread);
 
   if(buf[0]=='1')
   {
   	 fflush(stdin); // limpiar buffer  
     printf("\nRegresando al chat...\n");
   }
   else if(buf[0]=='2'){
     write(STDOUT_FILENO,"\nEl proceso termino la platica\n",31);
     sleep(3);
     kill(getppid(),SIGKILL); //terminar al proceso padre (xterm)
 
    }
    else { printf("Opcion no valida!\n"); }

}
 
void installusrhandlers()
{
    struct  sigaction  newact;
   
    newact.sa_handler = usr1handler;  /* nuevo usr1 handler */
    sigemptyset(&newact.sa_mask);    /* no se bloquean señales */
    newact.sa_flags = 0;            
    if (sigaction(SIGUSR1, &newact, (struct sigaction *)NULL) == -1) {
       perror("No pudo instalar manejador SIGUSR1 ");
       return;
    }
    
    newact.sa_handler = usr2handler;      /* nuevo handler */
    if (sigaction(SIGUSR2, &newact, (struct sigaction *)NULL) == -1) {
       perror("No pudo instalar manejador SIGUSR2 ");
       return;
    }
    newact.sa_handler = ctrl_handler;      /* nuevo handler */
    if (sigaction(SIGINT, &newact, (struct sigaction *)NULL) == -1) {
       perror("No pudo instalar manejador SIGINT\n"); //ctrl-c
       return;
    }

    fprintf(stderr,
       " Proceso %ld ha instalado interrupciones SIGUSR1, SIGUSR2 y SIGINT\n",
       (long)getpid());
}
 

/* funcion-hilo para leer desde tuberia */
void* do_lee(void* commfd)
{
    int communfd = *((int*)commfd);
    ssize_t bytesread;
    ssize_t byteswritten;
    char buf[BLKSIZE];

 	/*lee desde el socket */
    while( (bytesread = read(communfd, buf, BLKSIZE)) > 0) {
	
	/* y Escribir en pantalla */  
	write(STDOUT_FILENO, " r: ", 4);    
	byteswritten = write(STDOUT_FILENO, buf, bytesread);
       if (bytesread != byteswritten) {
          fprintf(stderr,
             "Error al escribir %ld bytes, %ld bytes escritos\n",
             (long)bytesread, (long)byteswritten);
          break;
       }
  
    } //fin while		

  pthread_exit(NULL);
} // fin do_lee

/* funcion-hilo para escribir a la tuberia*/
void* do_escribe(void* commfd)
{
    int communfd = *((int*)commfd);
    ssize_t bytesread;
    ssize_t byteswritten;
    char buf[BLKSIZE];

 	/*lee desde teclado */
    while(1) {
      bytesread = read(STDIN_FILENO, buf, BLKSIZE); 
       if ( (bytesread == -1) && (errno == EINTR) )
          fprintf(stderr, "No pudo leer de la entrada estandar\n");
       else 
	    if (bytesread <= 0) break;
         else {
          /* Escribir a la tuberia */
           byteswritten = write(communfd, buf, bytesread);

           if (byteswritten != bytesread) {
             fprintf(stderr,
                "Error al escribir %ld bytes, %ld bytes escritos\n",
                (long)bytesread, (long)byteswritten);
             break;
          }
	}
  
    } //fin while		

  pthread_exit(NULL);
} // fin do_escribe




int main (int argc, char *argv[]) {
  // parametros
  int tout=0;
  int tin=0;
  int np=0;

       
    if (argc != 4) {
        fprintf(stderr, "No se recibieron numeros de tuberias %s\n", argv[0]);
        exit(1);
    }
     
     //manejadores de señales  
    installusrhandlers();
    
    np = atoi(argv[1]); //numero de proceso
    tout = atoi(argv[2]); //numero de tubo - escribir
    tin  = atoi(argv[3]); //numero de tubo - leer

	printf("Iniciando platica, proceso %d - %d : ", np, getpid() );
	printf("con tuberias %2d  %2d\n", tout, tin );

 
	char *estado;
    int thr_id1; /* threads ID para nuevos hilos */
    int thr_id2;
	pthread_t p_thread1; /* estructuras thread */
	pthread_t p_thread2; 

	/* crear nuevos threads */

	thr_id2 = pthread_create(&p_thread2, NULL, do_escribe, (void*)&tout );	
	thr_id1 = pthread_create(&p_thread1, NULL, do_lee, (void*)&tin );

     /* el padre espera por la terminacion de los threads */
	pthread_join(p_thread2, (void**)&estado); 	
	pthread_join(p_thread1, (void**)&estado); 
	printf("Terminada %s la hebra \n", estado);
	printf("Terminada %s la hebra \n", estado);
 

    exit(0);

}

