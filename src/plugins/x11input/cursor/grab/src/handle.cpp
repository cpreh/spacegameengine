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


#include "../handle.hpp"
#include <sge/input/exception.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/sleep.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>

void
sge::x11input::cursor::grab::handle(
	cursor::grab::function const &_function,
	cursor::grab::return_value const _ok_value,
	cursor::grab::return_value_set const &_waiting_values
)
{
	cursor::grab::return_value ret;

	while(
		(
			ret =
				cursor::grab::return_value(
					_function()
				)
		)
		!= _ok_value
	)
	{
		if(
			_waiting_values.count(
				ret
			)
		)
			sge::time::sleep(
				sge::time::millisecond(
					10
				)
			);
		else
			throw sge::input::exception(
				FCPPT_TEXT("X11 grab failed with value ")
				+
				fcppt::lexical_cast<
					fcppt::string
				>(
					ret
				)
			);
	}
}
