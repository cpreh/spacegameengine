/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_KEYBOARD_HPP_INCLUDED
#define SGE_X11INPUT_KEYBOARD_HPP_INCLUDED

#include "keyboard_fwd.hpp"
#include "device.hpp"
#include "keyboard_grab_fwd.hpp"
#include <X11/Xlib.h>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <sge/input/keyboard/key_repeat_function.hpp>
#include <awl/backends/x11/window/event/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_ptr.hpp>
#include <awl/backends/x11/window/event/signal/connection_manager.hpp>
#include <awl/backends/x11/window/instance_ptr.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace x11input
{

class keyboard
:
	public sge::input::keyboard::device,
	public x11input::device
{
	FCPPT_NONCOPYABLE(
		keyboard
	)
public:
	keyboard(
		awl::backends::x11::window::instance_ptr,
		awl::backends::x11::window::event::processor_ptr
	);

	~keyboard();

	void
	grab();

	void
	ungrab();
private:
	fcppt::signal::auto_connection
	key_callback(
		input::keyboard::key_callback const &
	);

	fcppt::signal::auto_connection
	key_repeat_callback(
		input::keyboard::key_repeat_callback const &
	);

	sge::input::keyboard::mod_state const
	mod_state() const;

	void
	on_key_event(
		awl::backends::x11::window::event::object const &
	);

	awl::backends::x11::window::instance_ptr const window_;

	awl::backends::x11::window::event::processor_ptr const event_processor_;

	bool const need_grab_;

	awl::backends::x11::window::event::signal::connection_manager const connections_;

	fcppt::scoped_ptr<
		keyboard_grab
	> grab_;

	fcppt::signal::object<
		input::keyboard::key_function
	> key_signal_;

	fcppt::signal::object<
		input::keyboard::key_repeat_function
	> key_repeat_signal_;

	sge::input::keyboard::mod_state modifiers_;
};

}
}

#endif
