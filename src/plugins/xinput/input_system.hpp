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


#ifndef SGE_XINPUT_INPUT_SYSTEM_HPP
#define SGE_XINPUT_INPUT_SYSTEM_HPP

#include <cstddef>
#include <string>
#include <map>
#include "../../input/input_system.hpp"
#include "../../x_window.hpp"
#include "../../math/vector.hpp"
#include <boost/array.hpp>
#include <X11/extensions/xf86dga.h>

struct XModifierKeyMap;

namespace sge
{
namespace xinput
{

class input_system : public sge::input_system {
public:
	input_system(x_window_ptr wnd);
	~input_system();
	boost::signals::connection register_callback(const callback& c);
	void dispatch();
private:
	typedef int mouse_coordinate_t;
	void grab();
	void grab_pointer();
	void grab_keyboard();
	bool handle_grab(int return_value) const;
	void enable_dga(bool);
	key_type mouse_key(unsigned x11code) const;
	void warped_motion(XEvent&);
	void private_mouse_motion(mouse_coordinate_t deltax, mouse_coordinate_t deltay);

	signal_type sig;

	static const std::size_t key_array_size = 32;
	typedef boost::array<char,key_array_size> key_value_array;

	key_code get_key_code(KeySym ks) const;
	std::string get_key_name(KeySym ks) const;

	x_window_ptr wnd;
	XModifierKeymap* mmap;
	Colormap colormap;
	unsigned mmwidth;

	key_value_array last_keys;

	math::vector<mouse_coordinate_t,2> mouse_last;

	typedef std::map<unsigned,key_code> x11_to_sge_array;
	x11_to_sge_array x11tosge;

	struct _x_color {
		_x_color(Display* dsp, Colormap colormap)
		 : dsp(dsp), colormap(colormap), dealloc(false) {}
		~_x_color()
		{
			if(dealloc)
				XFreeColors(dsp, colormap, &color.pixel, 1, 0);
		}
		Display* dsp;
		Colormap colormap;
		bool dealloc;
		XColor color;
	};

	struct _x_pixmap {
		_x_pixmap(Display* dsp)
		 : dsp(dsp), pixmap(None) {}
		~_x_pixmap()
		{
			if(pixmap != None)
				XFreePixmap(dsp, pixmap);
		}
		Display* dsp;
		Pixmap pixmap;
	};

	struct _x_cursor {
		_x_cursor(Display* dsp)
		 : dsp(dsp), cursor(None) {}
		~_x_cursor()
		{
			if(cursor != None)
				XFreeCursor(dsp, cursor);
		}
		Display* dsp;
		Cursor cursor;
	};

	_x_color _black;
	_x_pixmap _no_bmp;
	_x_cursor _no_cursor;

#ifdef USE_DGA
	struct _dga_guard {
		_dga_guard(const x_window_ptr wnd) : enabled(false), wnd(wnd) {}
		~_dga_guard()
		{
			if(enabled)
				XF86DGADirectVideo(wnd->display(),wnd->screen(),0);
		}
		bool enabled;
		x_window_ptr wnd;
	};
	_dga_guard dga_guard;
#endif
	bool use_dga;
};

}
}

#endif

