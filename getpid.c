#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
 printf("ID del proceso: %ld\n", (long)getpid());
 printf("ID del padre: %ld\n", (long)getppid());
 printf("ID del usuario: %ld\n", (long)getuid());

 return 0;
}
