/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/src/model/md3/axis_array.hpp>
#include <sge/src/model/md3/max_qpath.hpp>
#include <sge/src/model/md3/read_string.hpp>
#include <sge/src/model/md3/read_vec3.hpp>
#include <sge/src/model/md3/tag.hpp>
#include <sge/src/model/md3/vec3.hpp>
#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::tag::tag(
	std::istream &_stream
)
:
	name_(
		sge::model::md3::read_string<
			sge::model::md3::max_qpath::value
		>(
			_stream
		)
	),
	origin_(
		sge::model::md3::read_vec3(
			_stream
		)
	),
	axis_(
		fcppt::algorithm::array_init<
			sge::model::md3::axis_array
		>(
			sge::model::md3::vec3::null()
		)
	)
{
	// FIXME: Initialize the array directly!
	for(
		auto &elem : axis_
	)
		elem =
			sge::model::md3::read_vec3(
				_stream
			);
}
