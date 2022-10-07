#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


    /*
    S_IRWXU
      Read, write, execute/search by owner.

    S_IRUSR
        Read permission, owner.
    S_IWUSR
        Write permission, owner.
    S_IXUSR
        Execute/search permission, owner.

    */

    mode_t permisosU(int permisos){
	switch(permisos){
		case 0: 
			return 0;	
			break;

		case 1:
			return  S_IXUSR;	
			break;

		case 2: 
			return S_IWUSR;	
			break;

		case 3:
			return  S_IXUSR | S_IWUSR;	
			break;

		case 4: 
			return S_IRUSR;
			break;

		case 5: 
			return S_IRUSR | S_IXUSR;	
			break;

		case 6:
			return S_IRUSR | S_IWUSR; 	
			break;
		case 7:
			return S_IRWXU;
			break; 
 
	}
    }

    
    /*
    S_IRWXG
        Read, write, execute/search by group.

    S_IRGRP
        Read permission, group.
    S_IWGRP
        Write permission, group.
    S_IXGRP
        Execute/search permission, group.

    */
    mode_t permisosG(int permisos){
          switch(permisos){
		case 0: 
			return 0;	
			break;

		case 1:
			return  S_IXGRP;	
			break;

		case 2: 
			return S_IWGRP;	
			break;

		case 3:
			return  S_IXGRP | S_IWGRP;	
			break;

		case 4: 
			return S_IRGRP;
			break;

		case 5: 
			return S_IRGRP | S_IXGRP;	
			break;

		case 6:
			return S_IRGRP | S_IWGRP; 	
			break;
		case 7:
			return S_IRWXG;
			break; 
 
	  }

    }


    /*
    S_IRWXO
        Read, write, execute/search by others.

    S_IROTH
        Read permission, others.
    S_IWOTH
        Write permission, others.
    S_IXOTH
        Execute/search permission, others.

    */
    mode_t permisosO(int permisos){
          switch(permisos){
		case 0: 
			return 0;	
			break;

		case 1:
			return  S_IXOTH;	
			break;

		case 2: 
			return S_IWOTH;	
			break;

		case 3:
			return  S_IXOTH | S_IWOTH;	
			break;

		case 4: 
			return S_IROTH;
			break;

		case 5: 
			return S_IROTH | S_IXOTH;	
			break;

		case 6:
			return S_IROTH | S_IWOTH; 	
			break;
		case 7:
			return S_IRWXO;
			break; 
 
	  }

    }


    mode_t mode(int z){
	int u, g, o;

	o= z%10;
	z/=10;	
	g= z%10;
	z/=10;
	u= z%10;

	return permisosU(u)|permisosG(g)|permisosO(o);
    }

    
    void decimalToBinary(int decimal, char *bin){
	
	int i=15;
	
	for(i=15;0 <= i;i--){
		bin[i]=(decimal%2)?'1':'0';
		decimal/=2;
	}
    }


    void VerPermisos( int modo){

	char permiso[10];
        int j,l,k=0;
	char cadena[]={ 0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0
		      };
	
	decimalToBinary(modo,cadena);

	for(j=0;j<9;j+=3){
		if( cadena[15-j]=='0')permiso[9-j]='-';
		else permiso[9-j]='x';
		if( cadena[15-j-1]=='0')permiso[9-j-1]='-';
		else permiso[9-j-1]='w';
		if( cadena[15-j-2]=='0')permiso[9-j-2]='-';
		else permiso[9-j-2]='r';
	}
	
		for(l=0;l<16;l++){
		printf("%c",cadena[l]);
		}
		printf("modo %d",modo);
		printf("\n");

	if(cadena[0]=='1' && cadena[2]=='1')
		permiso[0]='l';
	

	else if ( S_ISREG (modo) ){
	     permiso[0]='-';
		
   	     for(k=0;k<10;k++)
                   printf("%c",permiso[k]);
	     printf("\t");
	}
//	else{
   		else if(S_ISDIR(modo)){
		     permiso[0]='d';
		     for(k=0;k<10;k++)
                            printf("%c",permiso[k]);

		     printf("\t");//printf("%s ", name );
		}
/*		else if(!S_ISLNK(modo)){
		 permiso[0]='l';
		     for(k=0;k<10;k++)
                            printf("%c",permiso[k]);

		     printf("XA\t");
		}*/	
        //}

    }


    void printFileData(struct stat buffer,struct dirent *dir,struct passwd *pw){

         char sdate[256];
         struct tm *tm;
         struct group *grp;
         
         printf("%-9.9s\t",pw->pw_name);//nombre del propietario del archivo
     
         if( (grp=getgrgid(buffer.st_gid))!=NULL){
		printf("%-9.9s\t",grp->gr_name);//nombre del grupo del propietario
         }

         VerPermisos(buffer.st_mode); //permisos de archivo

         printf("%d  ", buffer.st_nlink); //numero de links fuertes
         printf("%s\t",dir->d_name);//nombre del archivo
         printf("%9jd\t",(intmax_t)buffer.st_size);//tamaño del archivo
         tm= localtime(&buffer.st_mtime);

         strftime(sdate, sizeof(sdate),nl_langinfo(D_T_FMT),tm);
         printf("%s\n", sdate);//Fecha de la ultima modificacion
    }


    int main(int argc,char **argv){

         struct dirent *dp;
         struct stat statbuf;
         struct passwd *pwd;
         DIR *dir;
         int band=0, flag=0,j;
    
	 int i=strlen(argv[1])-1;
         char *token, *file,*temp;
          
         switch(argc){
          
             case 2:
                   if ( (dir= opendir(".")) == NULL){//se abre el directorio actual
 	                perror("No se puede abrir el directorio");
                        return 1;
                   }
		   
                   file= (char*)malloc(strlen(argv[1])*sizeof(char)); 
           	   token=argv[1];

		   if(token[i]=='+'){
			flag=1;
                        for(j=0;j<i; j++){
                             file[j]=token[j];
                        }
                   }  

	           while((dp=readdir(dir))!=NULL ){
               
             	        if(strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..")==0){
                            continue; //se ignoran los archivos "." y ".."
              	        }
              	        else{
	                    if( !stat(dp->d_name,&statbuf)==-1)
		                continue;
                            else{
	                         switch(flag){
                                    case 0:
                                       if((pwd=getpwuid(statbuf.st_uid))!=NULL )
		 	                      if(strcmp(dp->d_name,argv[1])==0){
                               	    	            printFileData(statbuf,dp,pwd);
					            band=1;
				              }
                                    break;
                                    
                                    case 1:
                                       if((pwd=getpwuid(statbuf.st_uid))!=NULL ) 
                                             if(strstr(dp->d_name,file)!=0){ 
                                                    printFileData(statbuf,dp,pwd);
					            band=1;
				             }
                                    break;
                                 }
                    	       
                            }
                        }

                   }//while
               
                   if(band==0)
		        printf("\nNo se encontro el archivo!\n");

             break;

             case 4:
                   printf("\n\tFormato: ./accessmode chmod <permisos> <fichero> \n");  
                   printf("\tFormato: ./accessmode mkdir <fichero> <permisos> \n");

                   if(strcmp(argv[1],"chmod")==0){
	               chmod(argv[3],mode(atoi(argv[2])));
                   }else{
                         
                       if(argc==4 && strcmp(argv[1],"mkdir")==0){
                           mkdir(argv[2],mode(atoi(argv[3])));
                       }else{
                           printf("\n\tComando desconocido\n");
                       }
                   }

             break; 

             default :
                   printf("\n no hay argumentos suficientes");
                   printf("\n Modo de Empleo: accessmode [- m mascara] ficheros\n");
             break;
         }
         

         return 0;
}
