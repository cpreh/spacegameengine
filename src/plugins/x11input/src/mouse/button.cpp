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


#include <sge/x11input/mouse/button.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <fcppt/assert/pre.hpp>

sge::input::mouse::button const
sge::x11input::mouse::button(
	x11input::device::window_event const &_event,
	input::mouse::button_info_container const &_info
)
{
	int const detail(
		_event.get().detail
	);

	FCPPT_ASSERT_PRE(
		detail > 0
	)

	sge::input::mouse::button_id const id(
		static_cast<
			sge::input::mouse::button_id::value_type
		>(
			detail - 1 // TODO: why?
		)
	);

	FCPPT_ASSERT_PRE(
		id < _info.size()
	)

	return
		sge::input::mouse::button(
			_info[
				id
			].code(),
			id
		);
}
