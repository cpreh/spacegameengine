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


#include <sge/model/md3/impl/axis_array.hpp>
#include <sge/model/md3/impl/max_qpath.hpp>
#include <sge/model/md3/impl/read_string.hpp>
#include <sge/model/md3/impl/read_vec3.hpp>
#include <sge/model/md3/impl/tag.hpp>
#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/algorithm/array_init_move.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::impl::tag::tag(
	std::istream &_stream
)
:
	name_(
		sge::model::md3::impl::read_string<
			sge::model::md3::impl::max_qpath::value
		>(
			_stream
		)
	),
	origin_(
		sge::model::md3::impl::read_vec3(
			_stream
		)
	),
	axis_(
		fcppt::algorithm::array_init_move<
			sge::model::md3::impl::axis_array
		>(
			[
				&_stream
			]
			{
				return
					sge::model::md3::impl::read_vec3(
						_stream
					);
			}
		)
	)
{
}
