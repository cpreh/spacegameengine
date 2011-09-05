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


#include "read_and_check_id3p.hpp"
#include "endian.hpp"
#include <sge/model/md3/u8.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <istream>
#include <fcppt/config/external_end.hpp>

bool
sge::model::md3::read_and_check_id3p(
	std::istream &_stream
)
{
	typedef fcppt::container::array<
		md3::u8,
		4
	> id3p_array;

	id3p_array const to_check = { { 0x49, 0x44, 0x50, 0x33 } };

	id3p_array id3p;

	for(
		id3p_array::iterator it(
			id3p.begin()
		);
		it != id3p.end();
		++it
	)
		*it =
			fcppt::io::read<
				md3::u8
			>(
				_stream,
				md3::endian()
			);

	return
		std::equal(
			id3p.begin(),
			id3p.end(),
			to_check.begin()
		);
}
