#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define BLKSIZE 500 /*tamaño del buffer*/

int main(void)
{
int fd, bytes_read;
char buffer[BLKSIZE];
if ((fd = open("lectura.c", O_RDWR))==-1)
    perror("Error al abrir el fichero");
else
 {
   bytes_read = read(fd,buffer, BLKSIZE);
   buffer[bytes_read]='\0';
   printf("%s son %d \n", buffer,bytes_read);
 }
 system("pause");
 return(0);
}
