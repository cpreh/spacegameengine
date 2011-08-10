/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include "device_fwd.hpp"
#include "../input_context_fwd.hpp"
#include "../device/object.hpp"
#include "../device/parameters_fwd.hpp"
#include "../device/window_event_fwd.hpp"
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/char_function.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <sge/input/keyboard/key_repeat_function.hpp>
#include <awl/backends/x11/window/instance_fwd.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11input
{
namespace keyboard
{

class device
:
	public sge::input::keyboard::device,
	public sge::x11input::device::object
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		x11input::device::parameters const &,
		x11input::input_context const &
	);

	~device();

	void
	on_enter();

	void
	on_leave();
private:
	fcppt::signal::auto_connection
	key_callback(
		input::keyboard::key_callback const &
	);

	fcppt::signal::auto_connection
	key_repeat_callback(
		input::keyboard::key_repeat_callback const &
	);

	fcppt::signal::auto_connection
	char_callback(
		input::keyboard::char_callback const &
	);

	sge::input::keyboard::mod_state const
	mod_state() const;

	void
	on_key_press(
		x11input::device::window_event const &
	);

	void
	on_key_release(
		x11input::device::window_event const &
	);

	void
	update_modifiers(
		sge::input::keyboard::key_code::type,
		bool pressed
	);

	awl::backends::x11::window::instance &window_;

	x11input::input_context const &input_context_;

	fcppt::signal::connection_manager const connections_;

	fcppt::signal::object<
		input::keyboard::key_function
	> key_signal_;

	fcppt::signal::object<
		input::keyboard::key_repeat_function
	> key_repeat_signal_;

	fcppt::signal::object<
		input::keyboard::char_function
	> char_signal_;

	sge::input::keyboard::mod_state modifiers_;
};

}
}
}

#endif
