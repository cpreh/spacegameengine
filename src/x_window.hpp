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


#ifndef SGE_X_WINDOW_HPP_INCLUDED
#define SGE_X_WINDOW_HPP_INCLUDED

#include "./window.hpp"
#include <X11/Xlib.h>
#include <GL/glx.h>

namespace sge
{

class x_window : public window {
public:
	x_window(window_size sz, const std::string& title, Display* dsp, int screen, XVisualInfo* vi, Colormap& cmap);
	~x_window();

	void title(const std::string& title);
	void size(window_size sz);
	window_size size() const;
	const std::string& title() const;

	Window get_window() const;
	int screen() const;
	Display* display() const;
private:
	Window wnd;
	window_size sz;
	std::string _title;
	Display* dsp;
	int _screen;
	Visual* vi;
};

typedef shared_ptr<x_window> x_window_ptr;

}

#endif
