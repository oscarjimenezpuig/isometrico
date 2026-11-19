// Includes

#include "isometrico.h"

// Constantes

#define VOXSIZ 5 // define una arista del voxel
#define SCRW ((SPCX+SPCZ+2)*VOXSIZ) //dimension de la pantalla
#define SCRH ((2+SPCY+((SPCX>SPCZ)?SPCX:SPCZ))*VOXSIZ)
#define SCRCX ((1+SPCZ)*VOXSIZ) //centro de la pantalla
#define SCRCY ((1+SPCY)*VOXSIZ)

// Tipos

typedef unsigned long color_t
