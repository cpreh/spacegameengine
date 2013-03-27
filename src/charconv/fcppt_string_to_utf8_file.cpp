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


#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/fcppt_string_to_utf8_file.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


bool
sge::charconv::fcppt_string_to_utf8_file(
	fcppt::string const &_string,
	boost::filesystem::path const &_path
)
{
	boost::filesystem::ofstream file(
		_path
	);

	if(
		!file.is_open()
	)
		return false;

	sge::charconv::utf8_string const result(
		sge::charconv::fcppt_string_to_utf8(
			_string
		)
	);

	return
		!file.write(
			reinterpret_cast<
				char const *
			>(
				result.c_str()
			),
			static_cast<
				std::streamsize
			>(
				result.size()
			)
		).fail();
}
