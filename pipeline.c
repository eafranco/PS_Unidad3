// exec/pipeline.c: 
// redirige la salida estandar de un proceso a la entrada de otro
// debe ser los mismo que:  awk -F: '{print $5}' /etc/passwd | sort 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void productor(void) {
  execlp("awk", "awk", "-F:", "{print $5}", "/etc/passwd", NULL);
  perror("execlp");
  exit(1);
}
void consumidor(void) {
  execlp("sort", "sort", NULL); 
  perror("execlp");
  exit(1);
}
int main(void) {
int pid, tubo[2];
pipe(tubo);
if ((pid= fork())==0) {
	// 1 salida estandar de escritura (archivo)
  close(tubo[0]); dup2(tubo[1], 1); close(tubo[1]);
  productor();
}
else {
	// 0 salida estandar de lectura (pantalla)
  close(tubo[1]); dup2(tubo[0], 0); close(tubo[0]);
  consumidor();
}
}
