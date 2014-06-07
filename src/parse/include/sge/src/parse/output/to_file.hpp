/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_PARSE_OUTPUT_TO_FILE_HPP_INCLUDED
#define SGE_SRC_PARSE_OUTPUT_TO_FILE_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ofstream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace output
{

template<
	typename ToStream,
	typename Data
>
bool
to_file(
	ToStream const &_to_stream,
	boost::filesystem::path const &_path,
	Data const &_data
)
{
	fcppt::io::ofstream ofs(
		_path,
		std::ios_base::binary
	);

	if(
		!ofs.is_open()
	)
		throw
			sge::parse::exception(
				FCPPT_TEXT("Opening ")
				+
				fcppt::filesystem::path_to_string(
					_path
				)
				+
				FCPPT_TEXT(" failed!")
			);

	return
		_to_stream(
			ofs,
			_data
		);
}

}
}
}

#endif
