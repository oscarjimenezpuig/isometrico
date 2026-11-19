#include "isometrico.h"

space_t space;
principal_t principal;

#define forl(A,L) for((A)=0;(A)<(L);(A)++)
#define ilm(A,L) (A<L)

flag_t vox_is_nul(voxel_t v) {
    return v.vin;
}

void spc_clr() {
    ushort x,y,z;
    forl(x,SPCX) {
        forl(y,SPCY) {
            forl(z,SPCZ) {
                space[x][y][z]=VOXNUL;
            }
        }
    }
    principal.siz=0;
}

static flag_t pos_is_prc(ushort x,ushort y,ushort z) {
    ushort xx,yy,zz;
    xx=x;
    yy=y;
    zz=z;
    flag_t prc=1;
    while(1) {
        xx++;
        yy++;
        zz++;
        voxel_t vg;
        if(spc_get(&vg,xx,yy,zz)) {
            prc=0;
            break;
        } else if(xx>=SPCX || yy>=SPCY || zz>=SPCZ) break;
    }
    return prc;
}

static schar pos_cmp(point_t a,point_t b) {
    //comparamos dos puntos
    if(a.y>b.y) return 1;
    else if(a.y==b.y) {
        if(a.x>b.x) return 1;
        else if(a.x==b.x) {
            if(a.z>b.z) return 1;
            else if(a.z==b.z) return 0;
        }
    }
    return -1;
}

static flag_t prc_ins(short x,short y,short z) {
    point_t np={x,y,z};
    point_t* ptr=principal.pos;
    while(ptr!=principal.pos+principal.siz) {
        if(pos_cmp(*ptr,np)==1) break;
        else ptr++;
    }
    point_t* ltr=principal.pos+principal.siz;
    while(ltr!=ptr) {
        *ltr=*(ltr-1);
        ltr--;
    }
    *ptr=np;
    principal.siz++;
    return 1;
}

static point_t* prc_fnd(short x,short y,short z) {
    point_t np={x,y,z};
    point_t* ptr=principal.pos;
    while(ptr!=principal.pos+principal.siz) {
        if(pos_cmp(*ptr,np)==0) return ptr;
        ptr++;
    }
    return NULL;
}

static flag_t prc_era(point_t* ptr) {
    if(ptr) {
        while(ptr!=principal.pos+principal.siz) {
            *ptr=*(ptr+1);
            ptr++;
        }
        principal.siz--;
        return 1;
    }
    return 0;
}

static flag_t spc_son(short x,short y,short z,short* sx,short* sy,short* sz) {
    //dice si tiene x,y,z un hijo que esta oculto y lo devuelve (el primero)
    short xx,yy,zz;
    xx=x;
    yy=y;
    zz=z;
    voxel_t vp;
    while(1) {
        xx--;
        yy--;
        zz--;
        if(spc_get(&vp,xx,yy,zz)) {
            *sx=xx;
            *sy=yy;
            *sz=zz;
            return 1;
        } else if(xx<0 || yy<0 || zz<0) return 0;
    }
}       

flag_t spc_ins(ushort x,ushort y,ushort z,voxel_t v) {
    if(!vox_is_nul(v) && ilm(x,SPCX) && ilm(y,SPCY) && ilm(z,SPCZ)) {
        space[x][y][z]=v;
        if(pos_is_prc(x,y,z)) {
            short sx,sy,sz;
            if(spc_son(x,y,z,&sx,&sy,&sz)) {
                prc_era(prc_fnd(sx,sy,sz));
            }
            prc_ins(x,y,z);
        }
        return 1;
    }
    return 0;
}

flag_t spc_era(ushort x,ushort y,ushort z) {
    if(ilm(x,SPCX) && ilm(y,SPCY) && ilm(z,SPCZ)) {
        space[x][y][z]=VOXNUL;
        if(prc_era(prc_fnd(x,y,z))) {
            short sx,sy,sz;
            if(spc_son(x,y,z,&sx,&sy,&sz)) prc_ins(sx,sy,sz);
        }
        return 1;
    }
    return 0;
}

flag_t spc_get(voxel_t* v,ushort x,ushort y,ushort z) {
    if(ilm(x,SPCX) && ilm(y,SPCY) && ilm(z,SPCZ)) {
        *v=space[x][y][z];
        return !(vox_is_nul(*v));
    }
    return 0;
}

flag_t prc_get(uchar s,point_t* p) {
    static point_t* ptr=NULL;
    if(s) ptr=principal.pos;
    if(ptr) {
        *p=*ptr;
        ptr++;
        if(ptr>=principal.pos+principal.siz) ptr=NULL;
        return 1;
    } else return 0;
}

#include <stdio.h>

void prc_prt() {
    short k;
    forl(k,principal.siz) {
        point_t p=principal.pos[k];
        printf("(%i,%i,%i) ",p.x,p.y,p.z);
    }
    printf("\n");
}

//prueba

//TODO Esta prueba de orden no funciona, mirarla

int main() {
    spc_clr();
    voxel_t vox={1,1};
    spc_ins(0,0,0,vox);
    spc_ins(1,1,1,vox);
    spc_ins(2,2,2,vox);
    spc_ins(2,0,2,vox);
    spc_ins(1,1,0,vox);
    prc_prt();
    spc_era(1,1,1);
    prc_prt();
    spc_era(2,2,2);
    prc_prt();
}


