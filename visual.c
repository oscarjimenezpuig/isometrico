#include <X11/Xlib.h>
#include <X11/Xutil.h>

color_t BLACK=0;
color_t WHITE=0;

static Display* display=NULL;
static Colormap colormap;
static Window window;
static Pixmap virtual;
static GC graphic;
static color_t background;
static int min_key_code=0;
static int max_key_code=0;

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
		virtual=XCreatePixmap(display,window,w,h,xwa.depth);
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
		XFillRectangle(display,virtual,graphic,0,0,w,h);
		scr_fls();
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

void scr_bkg(color_t c) {
	background=c;
	scr_clr();
}

void pol_drw(color_t c,XPoint* p) {
    XForeground(display,graphic,c);
    XFillPolygon(display,window,graphic,p,4,Convex,CoorModeOrigin);
};




