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


#include <sge/model/md3/scalar.hpp>
#include <sge/src/model/md3/endian.hpp>
#include <sge/src/model/md3/read_vec3.hpp>
#include <sge/src/model/md3/vec3.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::model::md3::vec3 const
sge::model::md3::read_vec3(
	std::istream &_stream
)
{
	return
		md3::vec3(
			fcppt::io::read<
				md3::scalar
			>(
				_stream,
				md3::endian()
			),
			fcppt::io::read<
				md3::scalar
			>(
				_stream,
				md3::endian()
			),
			fcppt::io::read<
				md3::scalar
			>(
				_stream,
				md3::endian()
			)
		);
}
