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
	callback_handle register_callback(const callback& c);
	void dispatch();
private:
	signal_type sig;

	static const std::size_t key_array_size = 32;
	typedef boost::array<char,key_array_size> key_value_array;

	key_code get_key_code(KeySym ks) const;
	std::string get_key_name(KeySym ks) const;
	void update_modifiers(const key_value_array& keys);

	x_window_ptr wnd;
	XModifierKeymap* mmap;
	unsigned mmwidth;

	key_value_array last_keys;
	modifier_state modifiers;
	unsigned last_mouse;

	typedef std::map<unsigned,key_code> x11_to_sge_array;
	x11_to_sge_array x11tosge;

	struct _dga_guard {
		_dga_guard(const x_window_ptr wnd) : enabled(false), wnd(wnd) {}
		~_dga_guard()
		{
			if(enabled)
				XF86DGADirectVideo(wnd->get_display(),wnd->get_screen(),0);
		}
		bool enabled;
		x_window_ptr wnd;
	};
	_dga_guard dga_guard;
};

}
}

#endif

