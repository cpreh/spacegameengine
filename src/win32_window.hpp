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


#ifndef SGE_WIN32_WINDOW_HPP_INCLUDED
#define SGE_WIN32_WINDOW_HPP_INCLUDED

#include "string.hpp"
#include "window.hpp"
#include "windows.hpp"

namespace sge
{

class win32_window : public window {
public:
	win32_window(window_size sz, bool fullscreen, const string& title = "");
	~win32_window();

	void title(const string& t);
	void size(window_size newsize);
	window_size size() const;
	const string& title() const;
	HWND hwnd() const;
	bool fullscreen() const;
private:
	string      _title;
	bool        _fullscreen;
	bool        active;
	HWND        handle;
	static bool wndclass_created;
};

typedef shared_ptr<win32_window> win32_window_ptr;

}

#endif
