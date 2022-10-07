#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
int fd, bytes_escritos; /*descriptor de fichero*/
char buffer[100];
mode_t modo = S_IRWXU; /* modo de r, w y x para el propietario*/
strcpy(buffer, "Esto es un ejemplo\n");

if ((fd = open ("ejemplo.txt", O_RDWR | O_CREAT, modo))== -1)
    /*abre el fichero ejemplo en modo lectura/escritura o lo
       crea si no existe */
    perror ("Error al abrir o crear el fichero");
   /*muestra un mensaje de error si no puede abrir/crear el fichero*/
 else  
   bytes_escritos = write(fd, buffer, strlen(buffer));
    /* escribe buffer de tamaño sizeof(buffer) en fd */
system("pause");
exit(0);
}
