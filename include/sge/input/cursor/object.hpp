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


#ifndef SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/window_mode.hpp>
#include <sge/input/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

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
	virtual ~object();

	virtual fcppt::signal::auto_connection
	button_callback(
		cursor::button_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	move_callback(
		cursor::move_callback const &
	) = 0;

	virtual cursor::position const
	position() const = 0;

	virtual void
	visibility(
		bool
	) = 0;

	virtual void
	window_mode(
		cursor::window_mode::type
	) = 0;
};

}
}
}

#endif
