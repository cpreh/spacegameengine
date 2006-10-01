#ifndef SGE_GLX_HPP_INCLUDED
#define SGE_GLX_HPP_INCLUDED

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>

namespace sge
{

struct x_display {
	x_display() : d(XOpenDisplay(NULL)) { if(!d) throw std::runtime_error("XOpenDisplay failed or dsp is 0"); }
	~x_display() { XCloseDisplay(d); }
	operator Display*() { return d; }
	operator void*() { return d; }
	Display* d;
};
	
template<class T> struct x_resource {
	x_resource() : t(0){}
	x_resource(T t) : t(t) {}
	~x_resource() { if(t) XFree(t); }
	operator T() { return t; }
	x_resource& operator=(const T& _t) { t = _t; return *this; }
	T& operator->() { return t; }
	T* operator&() { return &t; }
	T t;
};

struct glx_context {
	glx_context(GLXContext c = 0, Display* dsp = 0) : c(c), dsp(dsp) {}
	~glx_context() { glXDestroyContext(dsp,c); }
	GLXContext c;
	Display* dsp;
};

struct x_colormap {
	x_colormap(Display* d, Colormap c) : d(d), c(c) {}
	~x_colormap() { XFreeColormap(d,c); }
	operator Colormap() { return c; }
	Display* d;
	Colormap c;
};

struct glx_current_guard {
	glx_current_guard(Display* d = 0) : d(d) {}
	~glx_current_guard() { if(d) glXMakeCurrent(d,None,NULL); }
	Display* d;
};

class xf86_resolution_guard {
public:
	xf86_resolution_guard(Display* dsp, int screen, XF86VidModeModeInfo* mode) : dsp(dsp), screen(screen), mode(mode) {}
	~xf86_resolution_guard() { XF86VidModeSwitchToMode(dsp,screen,mode); }
private:
	Display* dsp;
	int screen;
	XF86VidModeModeInfo* mode;
};

}

#endif
