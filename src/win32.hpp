#ifndef SGE_WIN32_HPP_INCLUDED
#define SGE_WIN32_HPP_INCLUDED

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace sge
{

struct win_hdc_hwnd {
	win_hdc_hwnd(HDC hdc = 0, HWND hwnd = 0) : hdc(hdc), hwnd(hwnd) {}
	~win_hdc_hwnd() { ReleaseDC(hwnd,hdc); }
	HDC hdc;
	HWND hwnd;
};

struct win_hglrc {
	win_hglrc(HGLRC hglrc = 0) : hglrc(hglrc) {}
	~win_hglrc() { wglDeleteContext(hglrc); }
	HGLRC hglrc;
	operator HGLRC() const { return hglrc; }
};

struct win_hdc {
	win_hdc(HDC hdc = 0) : hdc(hdc) {}
	~win_hdc() { DeleteDC(hdc); }
	HDC hdc;
	operator HDC() const { return hdc; }
};

template<typename T> struct win_object {
	win_object(T handle) : handle(handle) {}
	~win_object() { DeleteObject(handle); }
	T handle;
	operator T() const { return handle; }
};

}

#endif
