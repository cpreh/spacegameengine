#include "../types.hpp"
#ifdef SGE_LINUX_PLATFORM

#include "../x_window.hpp"
sge::x_window::x_window(const window_size sz, const std::string& _title, Display* const dsp, const int screen, XVisualInfo* const vi, Colormap& cmap)
	: sz(sz), _title(_title), _active(false), dsp(dsp), screen(screen)
{
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.border_pixel = 0;
	swa.background_pixel = 0;
	swa.override_redirect = True;
	swa.event_mask = FocusChangeMask | KeyPressMask | KeyReleaseMask | PropertyChangeMask | StructureNotifyMask | KeymapStateMask | PointerMotionMask;
	wnd = XCreateWindow(dsp,RootWindow(dsp,vi->screen),0,0,sz.w,sz.h,0,vi->depth, InputOutput, vi->visual, CWColormap /*| CWOverrideRedirect*/ | CWBorderPixel | CWEventMask, &swa);
	XStoreName(dsp,wnd,_title.c_str());
}

sge::x_window::~x_window()
{
	XDestroyWindow(dsp,wnd);
}

void sge::x_window::size(const window_size newsize)
{
	XResizeWindow(dsp,wnd,newsize.w,newsize.h);
}

void sge::x_window::title(const std::string& t)
{
	_title = t;
	XStoreName(dsp,wnd,_title.c_str());
}
/*
void sge::process_window_msgs()
{
	static Display* dsp = XOpenDisplay(NULL);

	XEvent event;
	while(XPending(dsp))
	{
		XNextEvent(dsp,&event);
	}
}*/

#endif
