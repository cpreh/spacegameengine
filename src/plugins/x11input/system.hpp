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


#ifndef SGE_X11INPUT_SYSTEM_HPP_INCLUDED
#define SGE_X11INPUT_SYSTEM_HPP_INCLUDED

#include <X11/Xlib.h>
#include "pointer.hpp"
#ifdef SGE_USE_DGA
#include "dga.hpp"
#endif
#include <sge/x11/color.hpp>
#include <sge/x11/pixmap.hpp>
#include <sge/x11/cursor.hpp>
#include <sge/x11/window.hpp>
#include <sge/input/system.hpp>
#include <sge/input/callback.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_type.hpp>
#include <sge/math/vector.hpp>
#include <sge/scoped_connection_manager.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signals.hpp>

namespace sge
{
namespace x11input
{

class system : public input::system {
public:
	explicit system(
		x11::window_ptr wnd);
	~system();

	callback_connection const
	register_callback(
		input::callback const &c);

	callback_connection const
	register_repeat_callback(
		input::repeat_callback const &c);

	void dispatch();
	window_ptr const get_window() const;
private:
	void grab();
	void grab_pointer();
	void grab_keyboard();
	bool handle_grab(int return_value) const;
	void enable_dga(bool);
	input::key_type mouse_key(unsigned x11code) const;
	void dga_motion(XEvent);
	void warped_motion(XEvent);
	void private_mouse_motion(mouse_coordinate_t deltax, mouse_coordinate_t deltay);
	input::key_type create_key_type(const XEvent&);

	void on_motion_event(const XEvent&);
	void on_key_event(const XEvent&);
	void on_button_event(const XEvent&);
	void on_acquire(const XEvent&);
	void on_release(const XEvent&);

	input::key_code get_key_code(KeySym ks) const;
	input::key_type::string get_key_name(KeySym ks) const;

	x11::window_ptr wnd;
	Colormap colormap;

	x11::color  black_;
	x11::pixmap no_bmp_;
	x11::cursor no_cursor_;
	bool        mouse_grabbed; // TODO: replace this with a RAII class
#ifdef SGE_USE_DGA
	dga dga_;
#endif
	bool use_dga;

	scoped_connection_manager connections;

	mouse_pos          mouse_last;
	
	typedef boost::signal<input::key_pair_fun> signal_type;
	typedef boost::signal<input::key_type_fun> repeat_signal_type;

	signal_type        sig;
	repeat_signal_type repeat_sig;
	
	static const input::key_type mouse_x,
	                             mouse_y,
	                             undefined_mouse_key,
	                             mouse_l,
	                             mouse_r,
	                             mouse_m;

};

}
}

#endif

