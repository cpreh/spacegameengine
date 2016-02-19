/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/optional_auto_connection_fwd.hpp>


namespace sge
{
namespace input
{

class SGE_CORE_DETAIL_CLASS_SYMBOL processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	processor();
public:
	//
	// keyboards
	//
	virtual
	fcppt::signal::optional_auto_connection
	keyboard_discover_callback(
		sge::input::keyboard::discover_callback const &
	) = 0;

	virtual
	fcppt::signal::optional_auto_connection
	keyboard_remove_callback(
		sge::input::keyboard::remove_callback const &
	) = 0;

	//
	// mice
	//
	virtual
	fcppt::signal::optional_auto_connection
	mouse_discover_callback(
		sge::input::mouse::discover_callback const &
	) = 0;

	virtual
	fcppt::signal::optional_auto_connection
	mouse_remove_callback(
		sge::input::mouse::remove_callback const &
	) = 0;

	//
	// foci
	//
	virtual
	fcppt::signal::optional_auto_connection
	focus_discover_callback(
		sge::input::focus::discover_callback const &
	) = 0;

	virtual
	fcppt::signal::optional_auto_connection
	focus_remove_callback(
		sge::input::focus::remove_callback const &
	) = 0;

	//
	// cursors
	//
	virtual
	fcppt::signal::optional_auto_connection
	cursor_discover_callback(
		sge::input::cursor::discover_callback const &
	) = 0;

	virtual
	fcppt::signal::optional_auto_connection
	cursor_remove_callback(
		sge::input::cursor::remove_callback const &
	) = 0;

	//
	// joypads
	//
	virtual
	fcppt::signal::optional_auto_connection
	joypad_discover_callback(
		sge::input::joypad::discover_callback const &
	) = 0;

	virtual
	fcppt::signal::optional_auto_connection
	joypad_remove_callback(
		sge::input::joypad::remove_callback const &
	) = 0;

	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~processor() = 0;
};

}
}

#endif
