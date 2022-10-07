
/*Programa que abre como archivo una terminal y escribe en ella.*/
#include <stdio.h>
#include  <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char **argv)  {
    /* abrimos la consola */
    /*system("gnome-terminal"); */
    int fd = open("/dev/pts/1", O_RDWR);
    /* el descriptor de fichero  devuelto por open es utilizado por write para escribir */
    write(fd, "hola joven!\n", 12);
    /* cerramos el fichero */
    exit(0); 
}
