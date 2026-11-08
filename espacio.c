#include "espacio.h"

space_t space;
plain_t plain;

#define forl(A,L) for((A)=0;(A)<(L);(A)++)

int vox_is_nul(voxel_t v) {
    return v.vox==0;
}

void spc_clr() {
    short x,y,z;
    forl(x,SPCX) {
        forl(y,SPCY) {
            forl(z,SPCZ) {
                space[x][y][z]=VOXNUL;
            }
        }
    }
    forl(x,PLAX) {
        forl(y,PLAY) {
            plain.vox[x][y]=VOXNUL;
        }
    
    }
    plain.chn=1;
}

#define ilm(A,L) ((A)>=0 && (A)<(L))

int spc_get(short x,short y,short z,voxel_t* vox) {
    if(ilm(x,SPCX) && ilm(y,SPCY) && ilm(z,SPCZ)) {
        *vox=space[x][y][z];
        return 1;
    }
    return 0;
}   

int spc_ins(short x,short y,short z,voxel_t vox) {
    voxel_t vfn;
    if(spc_get(x,y,z,&vfn) && vox_is_nul(vfn)) {
        space[x][y][z]=vox;
        uchar first=1;
        short xx,yy,zz;
        xx=x-1;
        yy=y-1;
        zz=z-1;
        voxel_t vde;
        while(!first && spc_get(xx,yy,zz,&vde)) {
            if(!vox_is_nul(vde)) first=0;
        }
        if(first) {
            short px=(x-z)+(SPCZ-1);
            short py=SPCY-1-(y-(x+z)/2);
            plain.vox[px][py]=vox;
            plain.chn=1;
        }
        return 1;
    }
    return 0;
}

//prueba

#include <stdio.h>

void prtpln() {
    short x,y;
    forl(y,PLAY) {
        forl(x,PLAX) {
            voxel_t vox=plain.vox[x][y];
            char c=(vox_is_nul(vox))?'.':'x';
            printf("%c",c);
        }
        printf("\n");
    }
    printf("\n");
}

void prti(int i) {
    printf("%i\n",i);
}

int main() {
    voxel_t vox={1,0};
    printf("%ix%i\n",PLAX,PLAY);
    spc_clr();
    prti(spc_ins(0,SPCY-1,0,vox));
    prti(plain.chn);
    prti(spc_ins(SPCX-1,SPCY-1,SPCZ-1,vox));
    prti(spc_ins(0,0,0,vox));
    prtpln();
    return 0;
}
    


