/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/x11/window_fwd.hpp>
#include <sge/input/system.hpp>
#include <sge/input/callback.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace input
{
class key_pair;
class key_type;
}

namespace x11input
{

class device;

class system : public input::system {
public:
	explicit system(
		x11::window_ptr wnd);
private:
	signal::auto_connection
	register_callback(
		input::callback const &c);

	signal::auto_connection
	register_repeat_callback(
		input::repeat_callback const &c);

	void dispatch();
	window::instance_ptr const window() const;

	void emit_callback(
		input::key_pair const &);
	void emit_repeat_callback(
		input::key_type const &);

	void on_key_event(XEvent const &);
	void on_acquire(XEvent const &);
	void on_release(XEvent const &);

	x11::window_ptr const wnd;
	bool                  acquired;

	typedef boost::ptr_vector<
		device
	> device_vector;

	device_vector devices;

	signal::connection_manager connections;

	typedef signal::object<input::key_pair_fun> signal_type;
	typedef signal::object<input::key_type_fun> repeat_signal_type;

	signal_type        sig;
	repeat_signal_type repeat_sig;
};

}
}

#endif

