
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
//que ocurrira

void trataAlarma (){
 printf("ha saltado la alarma \n");
}

int main () {
struct sigaction tratamiento; int pid;
pid = fork();
tratamiento.sa_handler = trataAlarma;
sigaction (SIGALRM, &tratamiento, 0);
if (pid != 0) {
alarm (2);
sleep (4);
kill (pid, SIGALRM);
}
if(pid == 0){
	pause();
	printf("soy el hijo: %d \n", pid);
}

return 0;
}