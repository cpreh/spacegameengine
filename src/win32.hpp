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
