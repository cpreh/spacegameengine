/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/choose_callback.hpp>
#include <sge/input/cursor/default_choose.hpp>
#include <sge/input/cursor/demuxer_fwd.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/object_set.hpp>
#include <sge/input/cursor/optional_object_ref.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/remove_event_fwd.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <sge/input/cursor/scroll_signal.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class SGE_CORE_DETAIL_CLASS_SYMBOL demuxer
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		demuxer
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	demuxer(
		sge::input::processor &,
		sge::input::cursor::choose_callback const &
			= sge::input::cursor::default_choose()
	);

	SGE_INPUT_DETAIL_SYMBOL
	~demuxer()
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	scroll_callback(
		sge::input::cursor::scroll_callback const &
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::optional_position const
	position() const
	override;

	SGE_INPUT_DETAIL_SYMBOL
	void
	mode(
		sge::input::cursor::mode
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::optional_object_ref const
	current_cursor() const;
private:
	void
	button_callback_internal(
		sge::input::cursor::button_event const &
	);

	void
	move_callback_internal(
		sge::input::cursor::move_event const &
	);

	void
	scroll_callback_internal(
		sge::input::cursor::scroll_event const &
	);

	void
	discover_callback(
		sge::input::cursor::discover_event const &
	);

	void
	remove_callback(
		sge::input::cursor::remove_event const &
	);

	void
	assign_cursor();

	sge::input::cursor::choose_callback const choose_;

	fcppt::signal::auto_connection_container const processor_connections_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	sge::input::cursor::scroll_signal scroll_signal_;

	sge::input::cursor::object_set cursors_;

	fcppt::signal::auto_connection_container cursor_connections_;

	sge::input::cursor::optional_object_ref current_cursor_;
};

}
}
}

#endif
