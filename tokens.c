//uso ed strtok en procesos padre e hijo
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
char *cadena="vine vi y venci a los tropas enemigas";
char *token;
char *separa=" ";	
token=strtok_r(cadena,separa);
printf(token);	
int pid;
/*pid = fork();
switch (pid)
{
 case 1: perror ("No se ha podido crear el hijo"); 
    break;
 case 0: 
	 do{ 
      printf("HIJO: %s\n", token);
	 } while( (token=(char *)strtok_r(NULL,separa))!= NULL);
    break;
 default: 
     do{ 
      printf("PADRE: %s\n", token);
	 } while( (token=(char *)strtok_r(NULL,separa))!= NULL);
}
*/
return 0;
}
