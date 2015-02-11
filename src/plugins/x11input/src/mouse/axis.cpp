/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/mouse/axis.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size_fun.hpp>


sge::input::mouse::axis const
sge::x11input::mouse::axis(
	sge::x11input::device::valuator::index const _index,
	sge::input::mouse::axis_info_container const &_info
)
{
	sge::input::mouse::axis_id const id(
		fcppt::strong_typedef_construct_cast<
			sge::input::mouse::axis_id,
			fcppt::cast::size_fun
		>(
			_index.get()
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
