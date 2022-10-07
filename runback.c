/* Programa 2.9: runback.c */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int makeargv(char *s, char *delimiters, char ***argvp);

int main(int argc, char *argv[]) {
   char **myargv;
   char delim[] = " \t";
   pid_t childpid;

   if (argc != 2) {
      fprintf(stderr, "Uso: %s string\n", argv[0]);
      exit(1);
   }
if ((childpid = fork()) == -1) {
      perror("Fallo el fork ");
      exit(1);
   } else if (childpid == 0) { /* el hijo se convierte en proceso en plano secundario */
     if (setsid() == -1)
        perror("No se puede convertir en lider de sesión");
     else if (makeargv(argv[1], delim, &myargv) < 0)
        fprintf(stderr, "No se pudo crear el arreglo de argumentos\n");
     else if (execvp(myargv[0], &myargv[0]) < 0)
        perror("Fallo la función exec");
     exit(1);      /* el hijo no debe regresar */
   }
   exit(0);    /* el padre termina */
}

//separa una cadena, según un delimitador y regresa un arreglo de tokens
int makeargv(char *s, char *delimiters, char ***argvp)
{
char *t;
char *snew;
int numtokens;
int i;
/* snew is real start of string after skipping leading delimiters */
snew = s + strspn(s, delimiters);
/* create space for a copy of snew in t */
if ((t = calloc(strlen(snew) + 1, sizeof(char))) == NULL) {
*argvp = NULL;
numtokens = -1;
} else { /* count the number of tokens in snew */
strcpy(t, snew);
if (strtok(t, delimiters) == NULL)
numtokens = 0;

else
for (numtokens = 1; strtok(NULL, delimiters) != NULL;
numtokens++)
;
/* create an argument array to contain ptrs to tokens */
if ((*argvp = calloc(numtokens + 1, sizeof(char *))) == NULL) {
free(t);
numtokens = -1;
} else { /* insert pointers to tokens into the array */
if (numtokens > 0) {
strcpy(t, snew);
**argvp = strtok(t, delimiters);
for (i = 1; i < numtokens + 1; i++)
*((*argvp) + i) = strtok(NULL, delimiters);
} else {
**argvp = NULL;
free(t);
}
}
}
return numtokens;
}

