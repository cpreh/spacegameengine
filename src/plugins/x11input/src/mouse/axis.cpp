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


#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_id.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/x11input/mouse/axis.hpp>
#include <fcppt/assert/pre.hpp>


sge::input::mouse::axis const
sge::x11input::mouse::axis(
	int const _code,
	input::mouse::axis_info_container const &_info
)
{
	FCPPT_ASSERT_PRE(
		_code >= 0
	);

	sge::input::mouse::axis_id const id(
		static_cast<
			sge::input::mouse::axis_id::value_type
		>(
			_code
		)
	);

	FCPPT_ASSERT_PRE(
		id < _info.size()
	);

	return
		sge::input::mouse::axis(
			_info[
				id
			].code(),
			id
		);
}
