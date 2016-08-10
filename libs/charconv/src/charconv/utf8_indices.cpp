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


#include <sge/charconv/index_vector.hpp>
#include <sge/charconv/utf8_bytes.hpp>
#include <sge/charconv/utf8_indices.hpp>
#include <sge/charconv/utf8_string.hpp>


sge::charconv::index_vector
sge::charconv::utf8_indices(
	sge::charconv::utf8_string const &_string
)
{
	sge::charconv::index_vector result{
		0u
	};

	for(
		sge::charconv::utf8_string::const_iterator it(
			_string.begin()
		);
		it < _string.end();
	)
	{
		unsigned const bytes{
			sge::charconv::utf8_bytes(
				*it
			)
		};

		result.push_back(
			result.back()
			+
			bytes
		);

		it +=
			bytes;
	}

	return
		result;
}
