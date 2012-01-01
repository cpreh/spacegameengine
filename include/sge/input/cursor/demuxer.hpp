/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/class_symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/choose_callback.hpp>
#include <sge/input/cursor/default_choose.hpp>
#include <sge/input/cursor/demuxer_fwd.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/object_ptr.hpp>
#include <sge/input/cursor/object_set.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/remove_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>


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
	);
public:
	SGE_INPUT_SYMBOL
	explicit demuxer(
		input::processor &,
		cursor::choose_callback const &
			= cursor::default_choose()
	);

	SGE_INPUT_SYMBOL
	~demuxer();

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	button_callback(
		cursor::button_callback const &
	);

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	move_callback(
		cursor::move_callback const &
	);

	SGE_INPUT_SYMBOL
	cursor::optional_position const
	position() const;

	SGE_INPUT_SYMBOL
	void
	mode(
		cursor::mode::type
	);

	SGE_INPUT_SYMBOL
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
		cursor::discover_event const &
	);

	void
	remove_callback(
		cursor::remove_event const &
	);

	void
	assign_cursor(
		cursor::object_ptr
	);

	cursor::choose_callback const choose_;

	fcppt::signal::connection_manager const processor_connections_;

	input::cursor::button_signal button_signal_;

	input::cursor::move_signal move_signal_;

	cursor::object_set cursors_;

	fcppt::signal::connection_manager cursor_connections_;

	cursor::object_ptr current_cursor_;
};

}
}
}

#endif
