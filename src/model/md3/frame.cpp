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


#include "frame.hpp"
#include "endian.hpp"
#include "read_string.hpp"
#include "read_vec3.hpp"
#include <sge/model/md3/scalar.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

sge::model::md3::frame::frame(
	std::istream &_stream
)
:
	min_bounds_(
		md3::read_vec3(
			_stream
		)
	),
	max_bounds_(
		md3::read_vec3(
			_stream
		)
	),
	local_origin_(
		md3::read_vec3(
			_stream
		)
	),
	radius_(
		fcppt::io::read<
			md3::scalar
		>(
			_stream,
			md3::endian()
		)
	),
	name_(
		md3::read_string<
			16
		>(
			_stream
		)
	)
{
}
