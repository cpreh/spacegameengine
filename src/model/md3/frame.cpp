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


#include <sge/src/model/md3/frame.hpp>
#include <sge/src/model/md3/read_scalar.hpp>
#include <sge/src/model/md3/read_string.hpp>
#include <sge/src/model/md3/read_vec3.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::frame::frame(
	std::istream &_stream
)
:
	min_bounds_(
		sge::model::md3::read_vec3(
			_stream
		)
	),
	max_bounds_(
		sge::model::md3::read_vec3(
			_stream
		)
	),
	local_origin_(
		sge::model::md3::read_vec3(
			_stream
		)
	),
	radius_(
		sge::model::md3::read_scalar(
			_stream
		)
	),
	name_(
		sge::model::md3::read_string<
			16
		>(
			_stream
		)
	)
{
}
