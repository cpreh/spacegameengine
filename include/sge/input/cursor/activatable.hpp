/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_CURSOR_ACTIVATABLE_HPP_INCLUDED
#define SGE_INPUT_CURSOR_ACTIVATABLE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/activatable_fwd.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <sge/input/cursor/scroll_signal.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class SGE_CORE_DETAIL_CLASS_SYMBOL activatable
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		activatable
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	activatable(
		sge::input::cursor::object &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~activatable()
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
	sge::input::cursor::optional_position
	position() const
	override;

	SGE_INPUT_DETAIL_SYMBOL
	void
	mode(
		sge::input::cursor::mode
	)
	override;

	SGE_INPUT_DETAIL_SYMBOL
	void
	active(
		bool
	);

	SGE_INPUT_DETAIL_SYMBOL
	bool
	active() const;
private:
	void
	on_button(
		sge::input::cursor::button_event const &
	);

	void
	on_move(
		sge::input::cursor::move_event const &
	);

	void
	on_scroll(
		sge::input::cursor::scroll_event const &
	);

	sge::input::cursor::object &cursor_;

	bool active_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	sge::input::cursor::scroll_signal scroll_signal_;

	fcppt::signal::auto_connection const
		button_connection_,
		move_connection_,
		scroll_connection_;
};

}
}
}

#endif
