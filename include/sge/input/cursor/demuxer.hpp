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


#ifndef SGE_INPUT_CURSOR_DEMUXER_HPP_INCLUDED
#define SGE_INPUT_CURSOR_DEMUXER_HPP_INCLUDED

#include <sge/input/cursor/demuxer_fwd.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/button_function.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/move_function.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/window_mode.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <set>

namespace sge
{
namespace input
{
namespace cursor
{

class SGE_CLASS_SYMBOL demuxer
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		demuxer
	)
public:
	SGE_SYMBOL
	explicit demuxer(
		input::processor_ptr
	);

	SGE_SYMBOL
	~demuxer();

	SGE_SYMBOL
	fcppt::signal::auto_connection
	button_callback(
		cursor::button_callback const &
	);

	SGE_SYMBOL
	fcppt::signal::auto_connection
	move_callback(
		cursor::move_callback const &
	);

	SGE_SYMBOL
	cursor::position const
	position() const;

	SGE_SYMBOL
	void
	window_mode(
		cursor::window_mode::type
	);

	SGE_SYMBOL
	cursor::object_ptr const
	current_cursor() const;
private:
	void
	button_callback_internal(
		cursor::button_event const &
	);

	void
	move_callback_internal(
		cursor::move_event const &
	);

	void
	discover_callback(
		cursor::object_ptr
	);

	void
	remove_callback(
		cursor::object_ptr
	);

	void
	assign_cursor(
		cursor::object_ptr
	);

	typedef fcppt::signal::object<
		cursor::button_function
	> button_signal;

	typedef fcppt::signal::object<
		cursor::move_function
	> move_signal;

	typedef std::set<
		cursor::object_ptr
	> cursor_set;

	fcppt::signal::connection_manager const processor_connections_;

	button_signal button_signal_;

	move_signal move_signal_;

	cursor_set cursors_;

	fcppt::signal::connection_manager cursor_connections_;

	cursor::object_ptr current_cursor_;
};

}
}
}

#endif
