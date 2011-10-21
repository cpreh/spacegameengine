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


#ifndef SGE_INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_INPUT_PROCESSOR_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/joypad/device_vector.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/device_vector.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/window/instance_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace input
{

class SGE_CLASS_SYMBOL processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
protected:
	SGE_INPUT_SYMBOL
	processor();
public:
	//
	// keyboards
	//
	virtual fcppt::signal::auto_connection
	keyboard_discover_callback(
		input::keyboard::discover_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	keyboard_remove_callback(
		input::keyboard::remove_callback const &
	) = 0;

	virtual input::keyboard::device_vector const
	keyboards() const = 0;

	//
	// mice
	//
	virtual fcppt::signal::auto_connection
	mouse_discover_callback(
		input::mouse::discover_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	mouse_remove_callback(
		input::mouse::remove_callback const &
	) = 0;

	virtual input::mouse::device_vector const
	mice() const = 0;

	//
	// cursors
	//
	virtual fcppt::signal::auto_connection
	cursor_discover_callback(
		input::cursor::discover_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	cursor_remove_callback(
		input::cursor::remove_callback const &
	) = 0;

	virtual input::cursor::object_vector const
	cursors() const = 0;

	//
	// joypads
	//
	virtual fcppt::signal::auto_connection
	joypad_discover_callback(
		input::joypad::discover_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	joypad_remove_callback(
		input::joypad::remove_callback const &
	) = 0;

	virtual input::joypad::device_vector const
	joypads() const = 0;

	//
	// other
	//
	virtual sge::window::instance_ptr const
	window() const = 0;

	SGE_INPUT_SYMBOL
	virtual ~processor() = 0;
};

}
}

#endif
