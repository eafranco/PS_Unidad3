#include <stdio.h>
#include  <fcntl.h> 
#include <stdlib.h>
int main (int argc, char **argv)  {
system("gnome-terminal"); 
/* abrimos la consola */ 
 int fd = open("/dev/pts/1", O_RDWR); 
/* el descriptor de fichero “fd” devuelto por open es utilizado por write para escribir */ 
///* cerramos el fichero */ 
exit(0); 
}
