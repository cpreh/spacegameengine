/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_XINPUT_INPUT_SYSTEM_HPP
#define SGE_XINPUT_INPUT_SYSTEM_HPP

#include <map>
#include <boost/signals/connection.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../../input/input_system.hpp"
#include "../../x_window.hpp"
#include "../../math/vector.hpp"
#include "pointer.hpp"
#include "x_color.hpp"
#include "x_pixmap.hpp"
#include "x_cursor.hpp"
#ifdef USE_DGA
#include "dga.hpp"
#endif

namespace sge
{
namespace xinput
{

class input_system : public sge::input_system {
public:
	input_system(x_window_ptr wnd);
	~input_system();
	callback_connection register_callback(const callback& c);
	callback_connection register_repeat_callback(const repeat_callback& c);
	void dispatch();
	window_ptr get_window() const;
private:
	void add_connection(boost::signals::connection);
	void grab();
	void grab_pointer();
	void grab_keyboard();
	bool handle_grab(int return_value) const;
	void enable_dga(bool);
	key_type mouse_key(unsigned x11code) const;
	void dga_motion(XEvent);
	void warped_motion(XEvent);
	void private_mouse_motion(mouse_coordinate_t deltax, mouse_coordinate_t deltay);
	key_type create_key_type(const XEvent&);

	void on_motion_event(const XEvent&);
	void on_key_event(const XEvent&);
	void on_button_event(const XEvent&);
	void on_acquire(const XEvent&);
	void on_release(const XEvent&);

	key_code get_key_code(KeySym ks) const;
	key_type::string get_key_name(KeySym ks) const;

	x_window_ptr wnd;
	Colormap colormap;

	x_color _black;
	x_pixmap _no_bmp;
	x_cursor _no_cursor;
#ifdef USE_DGA
	dga_guard _dga_guard;
#endif
	bool use_dga;
	typedef std::map<KeySym, key_code> x11_to_sge_array;
	x11_to_sge_array   x11tosge;

	boost::ptr_vector<boost::signals::scoped_connection> connections;

	mouse_pos          mouse_last;

	signal_type        sig;
	repeat_signal_type repeat_sig;
	
	static const key_type mouse_x,
	                      mouse_y,
	                      undefined_mouse_key,
	                      mouse_l,
	                      mouse_r,
	                      mouse_m;

};

}
}

#endif

