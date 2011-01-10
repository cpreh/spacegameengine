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


#include "cursor_grabber.hpp"
#include <sge/input/cursor/object.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/foreach.hpp>

sge::systems::cursor_grabber::cursor_grabber(
	sge::input::processor_ptr const _processor
)
:
	connection_(
		_processor->cursor_discover_callback(
			std::tr1::bind(
				&systems::cursor_grabber::cursor_discover,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	BOOST_FOREACH(
		input::cursor::object_vector::value_type cursor,
		_processor->cursors()
	)
		this->cursor_discover(
			cursor
		);
}

sge::systems::cursor_grabber::~cursor_grabber()
{
}

void
sge::systems::cursor_grabber::cursor_discover(
	sge::input::cursor::object_ptr const _cursor
)
{
	_cursor->window_mode(
		sge::input::cursor::window_mode::confine
	);
}
