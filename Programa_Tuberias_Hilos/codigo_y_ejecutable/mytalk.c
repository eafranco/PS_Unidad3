
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void p1(int t1out, int t2in) {
   char st1out[10], st2in[10];
   sprintf(st1out,"%2d",t1out); 
   sprintf(st2in,"%2d",t2in);

    // crear nueva terminal de control para P1
    // parametros de talkp: out (escribir), in (leer)
   if (execlp("xterm", "xterm", "-hold","-e","./talkp", "1",st1out,st2in,0) < 0)
        perror("Fallo la función exec\n");

   printf("Termino p1\n");  

  exit(0);
}


void p2(int t2out, int t1in) {
   char st2out[10], st1in[10];
   sprintf(st2out,"%2d",t2out); //cambiar a texto
   sprintf(st1in,"%2d",t1in);

    // crear nueva terminal de control para P2
    // parametros de talkp: out (escribir), in (leer)
   if (execlp("xterm", "xterm", "-hold","-e","./talkp","2",st2out,st1in, 0) < 0 )
        perror("Fallo la función exec\n");


   printf("Termino p2\n");  
   exit(0);
}

int main(void) {
int pid1, pid2, tubo1[2], tubo2[2] ;

pipe(tubo1);  //crear dos tuberias
pipe(tubo2);

printf("Ids de tuberias utilizadas: \n");
printf (" %d  %d \n", tubo1[1], tubo1[0]);
printf (" %d  %d \n", tubo2[1], tubo2[0]);

if ((pid1= fork())==0) { // creacion de proceso  si == 0 es copia del Hijo

   //close(tubo1[1]); 
   p2(tubo2[1],tubo1[0]);

 }
else {  // Padre
  if ((pid2= fork())==0) { // si == 0 es copia del segundo Hijo

      //close(tubo1[0]); 
      p1(tubo1[1],tubo2[0]);

     }
   else{ //proceso del padre
    int status1, status2;
    printf("\nEsperando por finalizacion de hijos\n Ctrl+C terminar y cerrar todo\n");
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    printf("Soy el padre y termino\n");
    exit(0);
  }
}

 return 0;
}


