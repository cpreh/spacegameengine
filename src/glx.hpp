/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GLX_HPP_INCLUDED
#define SGE_GLX_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>

namespace sge
{

struct x_display : boost::noncopyable {
	x_display() : d(XOpenDisplay(NULL)) { if(!d) throw std::runtime_error("XOpenDisplay failed or dsp is 0"); }
	~x_display() { XCloseDisplay(d); }
	Display* get() const { return d; }
private:
	Display* d;
};
	
template<typename T> struct x_resource : boost::noncopyable {
	x_resource() : t(0){}
	x_resource(const T t) : t(t) {}
	~x_resource() { if(t) XFree(t); }
	x_resource& operator=(const T& _t) { t = _t; return *this; }
	bool operator==(const T r) const { return t == r; }
	const T& operator->() const { return t; }
	const T& operator*() const { return t; }
	const T* pointer_to() const { return &t; }
	T get() { return t; }
	T* pointer_to() { return &t; }
private:
	T t;
};

struct glx_context : boost::noncopyable {
	glx_context(GLXContext c = 0, Display* const dsp = 0) : c(c), dsp(dsp) {}
	~glx_context() { glXDestroyContext(dsp,c); }
	GLXContext c;
	Display* dsp;
};

struct x_colormap : boost::noncopyable {
	x_colormap(Display* const d, Colormap c) : d(d), c(c) {}
	~x_colormap() { XFreeColormap(d,c); }
	operator Colormap() { return c; }
	Display* d;
	Colormap c;
};

struct glx_current_guard : boost::noncopyable {
	glx_current_guard(Display* const d = 0) : d(d) {}
	~glx_current_guard() { if(d) glXMakeCurrent(d,None,NULL); }
	Display* d;
};

class xf86_resolution_guard : boost::noncopyable {
public:
	xf86_resolution_guard(Display* const dsp, const int screen, const XF86VidModeModeInfo& mode) : dsp(dsp), screen(screen), mode(mode) {}
	~xf86_resolution_guard() { XF86VidModeSwitchToMode(dsp,screen,const_cast<XF86VidModeModeInfo*>(&mode)); 
	}
private:
	Display* dsp;
	int screen;
	const XF86VidModeModeInfo& mode;
};

}

#endif
