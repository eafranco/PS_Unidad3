/*Compilar con la opción: gcc -o chat_cliente2 chat_cliente2.c -pthread  */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h> /* pthread functions and data structures */
#include "uici.c"

#define BLKSIZE  1024

void usr1handler(int s)
{
   fprintf(stderr, "SIGUSR1 signal caught\n");
}
 
void usr2handler(int s)
{
   fprintf(stderr, "SIGUSR2 signal caught\n");
}
 
 
void installusrhandlers()
{
    struct  sigaction  newact;
    newact.sa_handler = usr1handler;      /* set the new usr1 handler */
    sigemptyset(&newact.sa_mask);    /* no additional signals blocked */
    newact.sa_flags = 0;            /* nothing special on the options */
    if (sigaction(SIGUSR1, &newact, (struct sigaction *)NULL) == -1) {
       perror("Could not install SIGUSR1 signal handler");
       return;
    }
    newact.sa_handler = usr2handler;      /* set the new usr2 handler */
    if (sigaction(SIGUSR2, &newact, (struct sigaction *)NULL) == -1) {
       perror("Could not install SIGUSR2 signal handler");
       return;
    }
    fprintf(stderr,
       "Client process %ld set to use SIGUSR1 and SIGUSR2\n",
       (long)getpid());
}
 


/* function1 to be executed by the new thread */
void* do_lee(void* commfd)
{
    int communfd = *((int*)commfd);
    ssize_t bytesread;
    ssize_t byteswritten;
    char buf[BLKSIZE];

 	/*lee desde el socket */
    while( (bytesread = u_read(communfd, buf, BLKSIZE)) > 0) {
	/* y Escribir en pantalla */       
	byteswritten = write(STDOUT_FILENO, buf, bytesread);
       if (bytesread != byteswritten) {
          fprintf(stderr,
             "Error writing %ld bytes, %ld bytes written\n",
             (long)bytesread, (long)byteswritten);
          break;
       }
  
    } //fin while		

  pthread_exit(NULL);
} // fin do_lee


/* function2 to be executed by the new thread */
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
          fprintf(stderr, "Server restarting read\n");
       else 
	if (bytesread <= 0) break;
         else {
          /* Escribir al socket */
           byteswritten = u_write(communfd, buf, bytesread);
           if (byteswritten != bytesread) {
             fprintf(stderr,
                "Error writing %ld bytes, %ld bytes written\n",
                (long)bytesread, (long)byteswritten);
             break;
          }
	}
  
    } //fin while		

  pthread_exit(NULL);
} // fin do_escribe


int main(int argc, char *argv[])
/*
 *  This is a client test of UICI. It opens a connection
 *  to a machine specified by host and a port number.
 *  It reads a file from stdin in blocks of size BLKSIZE
 *  and outputs it to the connection.
 */
{
    u_port_t portnumber;
    int outfd;
  
       
    if (argc != 3) {
        fprintf(stderr, "Usage: %s host port\n", argv[0]);
        exit(1);
    }
       
    installusrhandlers();
 
    portnumber = (u_port_t)atoi(argv[2]);
 
    if ((outfd = u_connect(portnumber, argv[1])) < 0) {
       u_error("Unable to establish an Internet connection");
       exit(1);
    }
       
    fprintf(stderr, "Connection has been made to %s\n", argv[1]);
 
	char *estado;
       int thr_id1; /* thread ID for the newly created thread */
       int thr_id2;
	pthread_t p_thread1; /* thread's structure */
	pthread_t p_thread2; /* thread's structure */

	/* crear nuevos threads */

	thr_id2 = pthread_create(&p_thread2, NULL, do_escribe, (void*)&outfd );	
	thr_id1 = pthread_create(&p_thread1, NULL, do_lee, (void*)&outfd );

       /* main espera por la terminacion de los threads */
	pthread_join(p_thread2, (void**)&estado); 	
	pthread_join(p_thread1, (void**)&estado); 
	printf("Terminada %s la hebra \n", estado);
	printf("Terminada %s la hebra \n", estado);
 
    u_close(outfd);
    exit(0);
}
