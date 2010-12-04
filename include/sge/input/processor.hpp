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


#ifndef SGE_INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_INPUT_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/device_vector.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace input
{

class SGE_CLASS_SYMBOL processor
{
	FCPPT_NONCOPYABLE(
		processor
	)
protected:
	SGE_SYMBOL processor();
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

	virtual keyboard::device_vector const
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

	virtual mouse::device_vector const
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

	virtual cursor::object_vector const
	cursors() const = 0;

	virtual cursor::object_ptr const
	main_cursor() const = 0;
	
	//
	// other
	//
	virtual sge::window::instance_ptr const
	window() const = 0;

	SGE_SYMBOL virtual ~processor();
};

}
}

#endif
