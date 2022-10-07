// pipe/ppipe1.c : 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void productor(int esc) {
  int i;
  for (i=1; i<=10; i++) {
    write(esc, &i, sizeof i); 
    sleep(1);
 }
exit(0);
}
void consumidor(int lec) {
   int leidos, i;
   while ((leidos = read(lec, &i, sizeof i)) > 0)
       printf("Recibido %d\n", i);
   exit(0);
}

int main(void) {
int pid, tubo[2];
pipe(tubo);
if ((pid= fork())==0) {
   close(tubo[1]);
   consumidor(tubo[0]);
 }
else {
   close(tubo[0]);
   productor(tubo[1]);
 }
}

