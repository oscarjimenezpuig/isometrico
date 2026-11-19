// Includes

#include <stddef.h>

// Constantes

#define SPCX 10 //dimensiones del espacio
#define SPCY 10
#define SPCZ 10

#define CHGS ((SPCX*SPCY)+(SPCX*SPCZ)*(SPCY*SPCZ) - SPCX - SPCZ -SPCY)

#define VOXNUL (voxel_t){1};

// Tipos

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned short ushort;

typedef unsigned char flag_t;

typedef struct {
    uchar vin : 1; //dice que el boxel es nulo
    uchar rot : 2; //rotacion del voxel
    uchar csu : 2; //color de la cara superior
    uchar csf : 2; //color de la frontal (eje x)
    uchar csi : 2; //color de la izquierda de la frontal
    uchar csd : 2; //color de la derecha de la frontal
    uchar cst : 2; //color de la trasera
} voxel_t;

typedef voxel_t space_t[SPCX][SPCY][SPCZ];

typedef struct {
    uchar x,y,z;
} point_t;

typedef struct{
    ushort siz;
    point_t pos[CHGS];
} principal_t;

// Variables

extern space_t space;
extern principal_t principal;

// Funciones

flag_t vox_is_nul(voxel_t vox);
//dice si un voxel es nulo

void spc_clr();
//se inicia el space con valores nulo y el principal con dimension 0

flag_t spc_ins(ushort x,ushort y,ushort z,voxel_t vox);
//se introduce un voxel en el espacio

flag_t spc_era(ushort x,ushort y,ushort z);
//se borra el voxel que ocupa la posicion dada

flag_t spc_get(voxel_t* vox,ushort x,ushort y,ushort z);
//conseguimos el voxel ocupado en una posicion

flag_t prc_get(uchar strt,point_t* point);
//se consigue el punto siguiente del principal, si strt conectado, empieza desde el principio
  
void prc_prt();
//impresion de todas las posiciones del principal en orden
