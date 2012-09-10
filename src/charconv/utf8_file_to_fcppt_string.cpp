/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/charconv/exception.hpp>
#include <sge/charconv/utf8_file_to_fcppt_string.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iterator>
#include <string>
#include <fcppt/config/external_end.hpp>


fcppt::string const
sge::charconv::utf8_file_to_fcppt_string(
	sge::charconv::system &charconv_system,
	boost::filesystem::path const &path)
{
	boost::filesystem::ifstream file_stream(
		path);

	if(!file_stream.is_open())
		throw
			sge::charconv::exception(
				FCPPT_TEXT("Couldn't open file \"")+
				fcppt::filesystem::path_to_string(
					path));

	return
		sge::charconv::utf8_string_to_fcppt(
			charconv_system,
			sge::charconv::utf8_string(
				std::istreambuf_iterator<char>(
					file_stream),
				std::istreambuf_iterator<char>()));
}
