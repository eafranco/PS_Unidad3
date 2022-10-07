//Multiplicacio de matrices
//con arreglos dinamicos hilos
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int **A, **B, **C;

void mult_mat(int nh, int fc, int cc)
{
  int i = 0;
	i = (nh==0)? 0: (nh/cc) ;
  int j = nh%cc;
  
  int suma=0;
   for (k=0; k<ca; k++)
     suma=suma+( A[i][k]*B[k][j] ) ;
   
    C[i][j]=suma;
}


int main(){
int fa,ca, fb,cb, fc,cc;

printf("Dimension de A: \n");
printf("Filas A: ");
scanf("%d",&fa);
printf("Columnas A: ");
scanf("%d",&ca);

printf("Dimension de B: \n");
printf("Filas B: ");
scanf("%d",&fb);
printf("Columnas B: ");
scanf("%d",&cb);

fc=fa;
cc=cb;


int i,k,j;


A = (int **) malloc(fa * sizeof(int) );
for(i=0; i<fa; i++) {
 A[i] = (int *) malloc(ca * sizeof(int) );
}

B = (int **) malloc(fb * sizeof(int) );
for(i=0; i<fb; i++) {
 B[i] = (int *) malloc(cb * sizeof(int) );
}

C = (int **) malloc(fc * sizeof(int) );
for(i=0; i<fc; i++) {
 C[i] = (int *) malloc(cc * sizeof(int) );
}



printf("Capturar A: \n");
for(i=0; i<fa; i++) 
{
 for(k=0; k<ca; k++) {
  printf("%d,%d: ",i,k); 
  scanf("%d", &A[i][k]);
 }
}

printf("\nMatriz A:");

for(i=0; i<fa; i++)
 {
 printf("\n");  
 for(k=0; k<ca; k++) {
   printf("%3d",A[i][k]);
 }
}

printf("\n");

printf("Capturar B: \n");
for(i=0; i<fb; i++) 
{
 for(k=0; k<cb; k++) {
  printf("%d,%d: ",i,k); 
  scanf("%d", &B[i][k]);
 }
}

printf("\nMatriz A:");

for(i=0; i<fb; i++)
 {
 printf("\n");  
 for(k=0; k<cb; k++) {
   printf("%3d",B[i][k]);
 }
}

printf("\n");

for(i=0; i<fc; i++) 
{
  
 for(j=0; j<cc; j++) 
  
 {
  
  int suma=0;
   for (k=0; k<ca; k++)
     suma=suma+( A[i][k]*B[k][j] ) ;
   
    C[i][j]=suma;
  } 
}

printf("\nMatriz C:");

for(i=0; i<fc; i++)
 {
 printf("\n");  
 for(k=0; k<cc; k++) {
   printf("%3d",C[i][k]);
 }
}

printf("\n");







 return 0;

}

