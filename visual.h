// Includes

#include "isometrico.h"

// Constantes

#define VOXSIZ 5 // define una arista del voxel
#define SCRW ((SPCX+SPCZ+2)*VOXSIZ) //dimension de la pantalla
#define SCRH ((2+SPCY+((SPCX>SPCZ)?SPCX:SPCZ))*VOXSIZ)
#define SCRCX ((1+SPCZ)*VOXSIZ) //centro de la pantalla
#define SCRCY ((1+SPCY)*VOXSIZ)
#define PALSIZ 4 //numero de colores de la paleta

// Tipos

typedef struct {
    uchar r,g,b;
} color_t;

typedef color_t palette_t[PALSIZ];

// Funciones

int scr_ini();
//inicio de la pantalla grafica

void scr_end();
//liberamos espacio de la pantalla grafica

void scr_fls();
//salida del grafico guardado

void scr_clr();
//limpiado de la pantallla grafica

void scr_bkg(color_t c);
//se establece un nuevo color para el fondo

void scr_pol_drw(XPoint* p,color_t col,uchar ind);
//se dibuja un cuadrilatero de color col con degradacion ind desde 1 a 3, donde 1 es el color real y 3 el maximo degradado

int key_lis();
//se escuchan las teclas (desde 'a' hasta 'z')

int key_in(key_t k);
//se comprueba si una tecla ha sido pulsada




