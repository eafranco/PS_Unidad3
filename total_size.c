#include <dirent.h>
#include <stdlib.h>

long int size_file( char *entrada)
 return 0;	

 void listar(const char *path)
	long int size=0, tsize=0;
			size=size_file(dp->d_name);
			tsize=tsize+size;
			//printf("%s %d \n", dp->d_name, dp->d_ino);
			//printf("nada\n");
		}
	
	printf("\nTotal de bytes ocupados: %ld\n",tsize);
	