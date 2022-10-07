/* Programa 2.10: simplebiff.c*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAILFILE "/var/spool/mail/linux"
#define SLEEPTIME 10

int main(void)
{
   int mailfd;
	int cont=0;

   for( ; ; ) {
      if ( (mailfd = open(MAILFILE, O_RDONLY)) != -1) {
         fprintf(stderr,"%s", "\007");
		  cont++;
		 fprintf(stderr,"Monitoreando el correo de linux %d\n",cont);
         close(mailfd);
      }  
      sleep(SLEEPTIME);
   }
  return 0; 



}
