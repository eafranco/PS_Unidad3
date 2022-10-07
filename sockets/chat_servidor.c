/* Program B.3 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "uici.c"

#define BLKSIZE  1024
void usr1handler(int s)
{
   fprintf(stderr, "SIGUSR1 signal caught by server\n");
}

void usr2handler(int s)
{
   fprintf(stderr, "SIGUSR2 signal caught by server\n");
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
       "Server process %ld set to use SIGUSR1 and SIGUSR2\n",
       (long)getpid());
}

int main(int argc, char *argv[])
/*
 *  This is a server which opens a connection to a
 *  port number and listens for a request.  It then
 *  opens a communication port and reads from the connection
 *  until the connection is terminated.   Each block that is
 *  read is echoed to standard out.
 */
{
    u_port_t portnumber;
    int listenfd;
    int communfd;
    ssize_t bytesread;
    ssize_t byteswritten;
    char buf[BLKSIZE];
    char remote[MAX_CANON];
       
    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }
       
    installusrhandlers();
 
    portnumber = (u_port_t)atoi(argv[1]);
 
    if ((listenfd = u_open(portnumber)) < 0) {
       u_error("Unable to establish a port connection");
       exit(1);
    }
       
    if ((communfd = u_listen(listenfd, remote)) < 0) {
       u_error("Failure to listen on server");
       exit(1);
    }
    fprintf(stderr, "Connection has been made to %s\n", remote);
      /*lee desde el socket */
    while( (bytesread = u_read(communfd, buf, BLKSIZE)) > 0) {
	/* Escribir en pantalla */       
	byteswritten = write(STDOUT_FILENO, buf, bytesread);
       if (bytesread != byteswritten) {
          fprintf(stderr,
             "Error writing %ld bytes, %ld bytes written\n",
             (long)bytesread, (long)byteswritten);
          break;
       }
       /* Leer desde el teclado */
       bytesread = read(STDIN_FILENO, buf, BLKSIZE);
       if ( (bytesread == -1) && (errno == EINTR) )
          fprintf(stderr, "Server restarting read\n");
       else if (bytesread <= 0) break;
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
    u_close(listenfd);
    u_close(communfd);
    exit(0);
}
