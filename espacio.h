// Definicion de un espacio en tres dimensiones que se proyectara isometricamente
// El espacio solo considerara las coordenadas positivas

// Constantes

#define SPCX 10 //Las tres dimensiones del espacio
#define SPCY 10
#define SPCZ 10

#define PLAX (SPCX+SPCZ)-1
#define PLAY (((MAX(SPCX,SPCZ)))+SPCY-1)

#define VOXNUL (voxel_t){0,0}

// Macros

#define MAX(A,B) (((A)>(B))?(A):(B))

// Tipos

typedef unsigned char uchar;
typedef unsigned short ushort;

typedef struct {
    ushort vox : 14; //identificador del voxel (0 implica vacio)
    ushort rot : 2; //rotacion del voxel (0 voxel original)
} voxel_t;

typedef voxel_t space_t[SPCX][SPCY][SPCZ];

typedef struct {
    voxel_t vox[PLAX][PLAY]; //es el mapa visual
    uchar chn; //bandera que indica que el plano ha cambiado
} plain_t;

// Variables

extern space_t space;
extern plain_t plain;

// Funciones

int vox_is_nul(voxel_t vox);
//dice si el voxel es nulo

void spc_clr();
//inicia el espacio y tambien el plano

int spc_get(short x,short y,short z,voxel_t* vox);

int spc_ins(short x,short y,short z,voxel_t vox);
//insercion de un voxel en una posicion del espacio

int spc_era(short x,short y,short z);
//borramos la posicion del espacio



