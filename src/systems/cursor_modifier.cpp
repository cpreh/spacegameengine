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


#include "cursor_modifier.hpp"
#include <sge/input/cursor/object.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>

sge::systems::cursor_modifier::cursor_modifier(
	sge::input::processor_ptr const _processor,
	systems::cursor_option_field const &_options
)
:
	options_(_options),
	connection_(
		_processor->cursor_discover_callback(
			std::tr1::bind(
				&systems::cursor_modifier::cursor_discover,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	input::cursor::object_vector const cursors(
		_processor->cursors()
	);

	for(
		input::cursor::object_vector::const_iterator it(
			cursors.begin()
		);
		it != cursors.end();
		++it
	)
		this->cursor_discover(
			*it
		);
}

sge::systems::cursor_modifier::~cursor_modifier()
{
}

void
sge::systems::cursor_modifier::cursor_discover(
	sge::input::cursor::object_ptr const _cursor
)
{
	if(
		options_ & systems::cursor_option::confine
	)
		_cursor->window_mode(
			sge::input::cursor::window_mode::confine
		);
	if(
		options_ & systems::cursor_option::hide
	)
		_cursor->visibility(
			false
		);
}
