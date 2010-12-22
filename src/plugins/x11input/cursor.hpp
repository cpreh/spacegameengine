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


#ifndef SGE_X11INPUT_CURSOR_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_HPP_INCLUDED

#include "cursor_fwd.hpp"
#include "device/object.hpp"
#include "device/parameters_fwd.hpp"
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/position.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11input
{

class cursor
:
	public sge::input::cursor::object,
	public x11input::device::object
{
	FCPPT_NONCOPYABLE(
		cursor
	)
public:
	explicit cursor(
		x11input::device::parameters const &
	);

	~cursor();

	void
	grab();

	void
	ungrab();
private:
	fcppt::signal::auto_connection
	button_callback(
		input::cursor::button_callback const &
	);

	fcppt::signal::auto_connection
	move_callback(
		input::cursor::move_callback const &
	);

	input::cursor::position const
	position() const;

	void
	show();

	void
	hide();
};

}
}

#endif
