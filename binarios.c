// Creación y uso de un archivo de acceso directo (binario)
//referencia de funciones: http://www.cplusplus.com/reference/clibrary/cstdio/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10

typedef struct {
	int id;
	char nom[30];
	float cal;
} Alumno;

int leeInt(){
	char str[15];
	int x;
	fgets(str,14,stdin);
	sscanf(str,"%d",&x);
	return x;
}

float leeFloat(){
	char str[15];
	float x;
	fgets(str,14,stdin);
	sscanf(str,"%f",&x);
	return x;
}



void inicializar();
void leer();
void escribir();

FILE* archivo;

void inicializar()
{
	Alumno nulo={-1,"",0.0};
	fseek(archivo, 0 , SEEK_SET);
	for(int i=0; i<N; i++) {
	 fwrite(&nulo,sizeof(Alumno),1,archivo);
    }
}

int main() {
	
	archivo = fopen("fseek.txt","w+b");//abre para lectura y escritura, binario
	if (archivo==NULL) { printf("No se pudo abrir el archivo."); exit(1); }
	inicializar();
	int opcion=-1;
	while(opcion!=0)
	{
		printf("Que desea hacer?  1-Escribir    2-Leer. \nIngrese 0 para salir\n");
		//scanf("%d",&opcion);
		//fflush(stdin);
		opcion=leeInt();
		
		switch(opcion)
		{
		case 0:
			printf("Saliendo del sistema!\n");
			break;
		case 1:
			escribir();
			break;
		case 2:
			leer();
			break;
		
		default:
			printf("Opcion no valida!\n");
		}
		
		//system("Pause");
	}
	fclose(archivo);
	return 0;
}


//Lee del archivo y muestra en pantalla
void leer()
{
	int x;
	Alumno nuevo;
	printf("Ingresa id de alumno entre 1 y %d: ",N);
	//scanf("%d",&x);
	x=leeInt();
	x--;
	fseek(archivo,sizeof(Alumno)*x, SEEK_SET); //desde el inicio
	fread(&nuevo,sizeof(Alumno),1,archivo);
	printf("Id: %d\n",nuevo.id);
	printf("nombre: %s\n",nuevo.nom);
	printf("calificacion: %.2f\n",nuevo.cal);
}

//Lee del teclado y escribe en disco, según ID (entre 1 y N) 
void escribir()
{
	// Escribir aqui el código faltante
	
}

void borrar(){
	
	// Escribir aqui el código faltante
	
}
