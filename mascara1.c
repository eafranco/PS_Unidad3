//uso de mascaras de señales
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
alarm(25);
printf("Intenta salir de esto...\n");
sleep(10);
printf("Termino de dormir\n");
// desbloquear señales
//if(sigprocmask(SIG_UNBLOCK, &dossigs, NULL)) 
//	 perror("No se pudo desbloquear señales\n");
for(;;){	
}
printf("Algo no se configuro bien...\n");
return 0;
}
