/* Programa: makeargv.c */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
* Make argv array (*arvp) for tokens in s which are separated by
* delimiters. Return -1 on error or the number of tokens otherwise.
*/
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


int main(){
char **params;
int i, numtokens=0;
char orden[]="ls -l -e -x";

if ((numtokens = makeargv(orden, " \t", &params)) < 0) 
{
fprintf(stderr,
"Could not construct argument array for %s\n", orden);
exit(1);
} 
else {
printf("The argument array contains:\n");
for (i = 0; i < numtokens; i++)
printf("[%d]:%s\n", i, params[i]);
}

return 0;
}
