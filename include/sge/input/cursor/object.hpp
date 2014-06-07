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


#ifndef SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class SGE_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
protected:
	SGE_INPUT_SYMBOL
	object();
public:
	SGE_INPUT_SYMBOL
	virtual
	~object() = 0;

	virtual
	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	) = 0;

	virtual
	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	) = 0;

	virtual
	fcppt::signal::auto_connection
	scroll_callback(
		sge::input::cursor::scroll_callback const &
	) = 0;

	virtual
	sge::input::cursor::optional_position const
	position() const = 0;

	virtual
	void
	mode(
		sge::input::cursor::mode
	) = 0;
};

}
}
}

#endif
