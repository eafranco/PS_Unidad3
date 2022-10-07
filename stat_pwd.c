//stat_pwd.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h> 
 
int main(int argc, char *argv[])
{
    struct stat statbuf; 
    struct passwd *pwd; 
    
    
    if (argc != 2) {
       fprintf(stderr, "Usar: %s nombre de archivo\n", argv[0]);
       exit(1);
    }
    if (stat(argv[1], &statbuf) == -1) {
       fprintf(stderr, "No se pudo usar stat sobre el archivo %s: %s\n",
               argv[1], strerror(errno));
       exit(1);
    }
    if (statbuf.st_mode & S_IFDIR) {  // determinar si es un directorio 0000010000000
        printf("\n %s es un directorio: ", argv[1]);
        printf("ultima modificacion:  %s\n", ctime(&statbuf.st_mtime));
    } else
        printf("%s no es un directorio\n", argv[1]);
        
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL) 
    //if ((pwd = getpwnam("Enrique")) != NULL) 
	     printf("Propietario: %-8.8s \n", pwd->pw_name); 
    else 	
	     printf("Iid del propietario: %-8d \n", statbuf.st_uid);
    
        
        
    return (0);
}



