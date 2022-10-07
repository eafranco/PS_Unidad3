//alarma2.c   usa máscara de señales que serán bloquedas
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
int main (void)
{


sigset_t dossigs;
// inicializar mascaras
sigemptyset(&dossigs);
sigaddset(&dossigs, SIGINT);  
sigaddset(&dossigs, SIGQUIT);  
sigaddset(&dossigs, SIGKILL);  
sigaddset(&dossigs, SIGTERM);  	
// aplicar mascara
if(sigprocmask(SIG_BLOCK, &dossigs, NULL)) 
   perror("No se pudo bloquear señales\n");

alarm(5);
printf("Espero 5 segundos para terminar...\n");
alarm(10);
printf("no mejor 6 segundos ...\n");
for(;;){ 
  printf(".");
  printf("-");

  sleep(1);
}
printf("No creo llegar hasta aqui...\n");

if(sigprocmask(SIG_UNBLOCK, &dossigs, NULL)) 
	 perror("No se pudo desbloquear señales\n");


return 0;
}
