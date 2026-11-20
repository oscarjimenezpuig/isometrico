#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "visual.h"

// Variables

static Display* display=NULL;
static Colormap colormap;
static Window window;
static Pixmap virtual;
static GC graphic;
static unsigned long background;
static int min_key_code=0;
static int max_key_code=0;
static ulong BLACK=0;
static ulong WHITE=0;

// Funciones Color

static ulong col_new(color_t c) {
    const ushort FAC=257;
	XColor xc;
	xc.flags=DoRed|DoGreen|DoBlue;
	xc.red=FAC*c.r;
	xc.green=FAC*c.g;
	xc.blue=FAC*c.b;
	XAllocColor(display,colormap,&xc);
	return xc.pixel;
}

// Funciones de Ventana

int scr_ini() {
	int screenum=0;
	display=XOpenDisplay(0);
	if(display) {
		int screennum=XDefaultScreen(display);
		colormap=XDefaultColormap(display,screenum);
		BLACK=col_new(0,0,0);
		WHITE=col_new(255,255,255);
		window=XCreateSimpleWindow(display,RootWindow(display,screennum),0,0,SCRW,SCRH,0,0,0);
		XWindowAttributes xwa;
		XGetWindowAttributes(display,window,&xwa);
		virtual=XCreatePixmap(display,window,SCRW,SCRH,xwa.depth);
		static XGCValues gv;
		gv.line_width=1;
		gv.foreground=WHITE;
		gv.background=background=BLACK;
		graphic=XCreateGC(display,window,GCForeground|GCBackground|GCLineWidth,&gv);
		XSelectInput(display,window,StructureNotifyMask|KeyPressMask|KeyReleaseMask);
		XMapWindow(display,window);
		XEvent event;
		int mapped=0;
		while(XEventsQueued(display,QueuedAlready) || !mapped) {
			XNextEvent(display,&event);
			mapped=(!mapped)?(event.type==MapNotify):1;
		}
		XDisplayKeycodes(display,&min_key_code,&max_key_code);
		XSetForeground(display,graphic,gv.background);
		XFillRectangle(display,virtual,graphic,0,0,SCRW,SCRH);
		return 1;
	}
	return 0;
}

void scr_end() {
	XUnmapWindow(display,window);
	XDestroyWindow(display,window);
	XFreePixmap(display,virtual);
	XFreeColormap(display,colormap);
	XFreeGC(display,graphic);
	XEvent e;
	while(XEventsQueued(display,QueuedAlready)) {
			XNextEvent(display,&e);
	}
	XCloseDisplay(display);
}

void scr_fls() {
   XCopyArea(display,virtual,window,graphic,0,0,SCRW,SCRH,0,0);
	while(XPending(display)==0);
	XFlush(display);
}

void scr_clr() {
    XSetForeground(display,graphic,background);
    XFillRectangle(display,virtual,graphic,0,0,SCRW,SCRH);
}

void scr_bkg(color_t col) {
	background=col_new(col);
	scr_clr();
}

static void pol_drw(ulong c,XPoint* p) {
    XSetForeground(display,graphic,c);
    XFillPolygon(display,window,graphic,p,4,Convex,CoordModeOrigin);
};


// Funciones Teclado

#define FKEY 'a' //primera de las letras
#define KEYS ('z'-'a'+1) //numero de teclas que pueden ser pulsadas
#define ARKD ((KEYS/8)+((KEYS%8==0)?0:1)) //dimension del array de teclas

static uchar keyprs[ARKD];

int key_lis() {
    XEvent ev;
    KeySym ks;
    int ty=0;
    while(XPending(display)>0) {
        XNextEvent(display,&ev);
        ty=(ev.type==KeyPress)?1:(ev.type==KeyRelease)?-1:0;
        if(ty) {
            ks=XLookupKeysym(&ev.xkey,0);
            char k='a'+(ks-XK_a);
            if(k>='a' && k<='z') {
                uchar* ptr=keyprs+(k-FKEY)/8;
                uchar flg=1<<(k-FKEY)%8;
                if(ty==1) *ptr|=flg;
                else *ptr&=(~flg);
            }
        }
    }
    return ty;
}                 

int key_in(key_t k) {
    if(k>=FKEY && k<FKEY+KEYS) return keyprs[(k-FKEY)/8] & (1<<(k-FKEY)%8);
    else return 0;
}



