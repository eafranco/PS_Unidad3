#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 512

int main( int argc, char **argv )
{
pid_t pid;
int p[2], p2[2], readbytes, readbytes2, i;
char buffer[SIZE], buffer2[SIZE];
pipe( p );  // crear la tuberia
pipe( p2 ); 

if ( (pid=fork()) == 0 )
{ // hijo
 close( p[1] ); /* cerramos el lado de escritura del pipe */
 while( (readbytes=read( p[0], buffer, SIZE )) > 0) 
 {
  // write( 1, buffer, readbytes );
  buffer[readbytes]='\0';
 }
 close( p[0] );

 printf("leidos: %d", (int)strlen(buffer));

 for( i=0; i<strlen(buffer); i++){
   buffer[i]=toupper(buffer[i]);
  // printf("%c",buffer[i]);
 }
 
 //enviar al padre
 close( p2[0] ); /* cerramos el lado de lectura del pipe */
 write( p2[1], buffer, strlen(buffer) );
 close( p2[1] ); 
}
else
{ // padre
 close( p[0] ); /* cerramos el lado de lectura del pipe */
 strcpy( buffer, "Esto llega a traves de la tuberia\n" );
 write( p[1], buffer, strlen( buffer ) );
 close( p[1] );
 close( p2[1] ); 
 while( (readbytes2=read( p2[0], buffer2, SIZE )) > 0)
  write( 1, buffer2, readbytes2 );
 close( p2[0]);
  

}

waitpid( pid, NULL, 0 );
exit( 0 );
}




