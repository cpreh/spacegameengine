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


#include <sge/model/md3/u8.hpp>
#include <sge/src/model/md3/endian.hpp>
#include <sge/src/model/md3/read_and_check_id3p.hpp>
#include <fcppt/io/read_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <array>
#include <istream>
#include <fcppt/config/external_end.hpp>


bool
sge::model::md3::read_and_check_id3p(
	std::istream &_stream
)
{
	typedef std::array<
		md3::u8,
		4
	> id3p_array;

	id3p_array const to_check{{
		0x49, 0x44, 0x50, 0x33
	}};

	id3p_array id3p;

	for(
		auto &elem : id3p
	)
		elem =
			fcppt::io::read_exn<
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
