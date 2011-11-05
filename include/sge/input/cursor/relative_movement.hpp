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


#ifndef SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_RELATIVE_MOVEMENT_HPP_INCLUDED

#include <sge/input/symbol.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/relative_move_callback.hpp>
#include <sge/input/cursor/relative_move_function.hpp>
#include <sge/input/cursor/relative_movement_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class relative_movement
{
	FCPPT_NONCOPYABLE(
		relative_movement
	);
public:
	SGE_INPUT_SYMBOL
	explicit relative_movement(
		cursor::object &
	);

	SGE_INPUT_SYMBOL
	~relative_movement();

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	relative_move_callback(
		cursor::relative_move_callback const &
	);
private:
	void
	move_callback_internal(
		cursor::move_event const &
	);

	typedef fcppt::signal::object<
		cursor::relative_move_function
	> relative_move_signal;

	cursor::object &cursor_;

	cursor::optional_position last_position_;

	relative_move_signal relative_move_signal_;

	fcppt::signal::scoped_connection const connection_;
};

}
}
}

#endif
