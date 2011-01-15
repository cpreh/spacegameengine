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


#ifndef SGE_DINPUT_CURSOR_HPP_INCLUDED
#define SGE_DINPUT_CURSOR_HPP_INCLUDED

#include "cursor_fwd.hpp"
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_function.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_function.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/window_mode.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_ptr.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{

class cursor
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		cursor
	)
public:
	explicit cursor(
		awl::backends::windows::window::event::processor_ptr
	);

	~cursor();

	fcppt::signal::auto_connection
	button_callback(
		input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		input::cursor::move_callback const &
	);

	input::cursor::position const
	position() const;

	void
	window_mode(
		input::cursor::window_mode::type
	);

	void
	acquire();

	void
	unacquire();
private:
	awl::backends::windows::window::event::return_type
	on_move(
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_button(
		awl::backends::windows::window::event::object const &,
		sge::input::cursor::button_code::type,
		bool down
	);

	typedef fcppt::signal::object<
		input::cursor::button_function
	> button_signal;

	typedef fcppt::signal::object<
		input::cursor::move_function
	> move_signal;

	button_signal button_signal_;

	move_signal move_signal_;

	fcppt::signal::connection_manager const connections_;
};

}
}

#endif
