/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/impl/set_pressed_if_appropriate.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/optional_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::camera::impl::set_pressed_if_appropriate(
	bool &_result,
	sge::input::key::optional_code const &_optional_key,
	sge::input::keyboard::key_event const &_key_event
)
{
	fcppt::optional::maybe_void(
		_optional_key,
		[
			&_key_event,
			&_result
		](
			sge::input::key::code const _code
		)
		{
			if(
				_code
				==
				_key_event.key().code()
			)
				_result =
					_key_event.pressed();
		}
	);
}
