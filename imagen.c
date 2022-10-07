/*******************************************
*   Introduccion a SDL               *

agregar a las opciones de compilacion:  -lmingw32 -lSDLmain -lSDL
ver como instalar en: http://www.losersjuegos.com.ar/referencia/articulos/instalar_devcpp
descargar desde: http://www.libsdl.org/download-1.2.php 
y copiar en lib, en include y el .dll en el dir actual
***************************************/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
 
int main(int argc, char *argv[])
 {
  SDL_Surface *screen;
  SDL_Surface *fondo;
  SDL_Surface *protagonista;
  SDL_Rect destino;
  int i, j;
	
  /* Tratamos de inicializar la biblioteca SDL */
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
     exit(1);
   }
   
   /* Preparamos las imagenes a mostrar */
  fondo = SDL_LoadBMP("fondo.bmp");
  protagonista = SDL_LoadBMP("protag.bmp");
  
  /* Si todo ha ido bien, hacemos algo: 
      entrar a modo grafico y cambiar el título de la ventana */
  screen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE );
  if( screen == NULL ) {
     printf( "Error al entrar a modo grafico: %s\n", SDL_GetError() );
     SDL_Quit();
      return -1;
   }
  
   /* Titulo de la ventana */
   SDL_WM_SetCaption( "Hola mundo 2!", "Hola Mundo 2!" );
  
  /* Dibujamos la imagen de fondo */
  /* Como tiene 207 x 211 pixeles, la repetimos varias veces */
  for (i=0; i<3; i++)
	for (j=0; j<3; j++) {
      destino.x=207*i;
       destino.y=211*j;
       SDL_BlitSurface(fondo, NULL, screen, &destino);
 	}
 
   /* Dibujamos el protagonista */
   destino.x=320;
   destino.y=400;
   SDL_BlitSurface(protagonista, NULL, screen, &destino);
 
   /* Actualizamos la pantalla */
   SDL_Flip(screen);
  
  /* Y esperamos antes de salir */
  SDL_Delay( 5000 );
   
   /* Finalmente, preparamos para salir */
   SDL_Quit();
   return 0;
}

