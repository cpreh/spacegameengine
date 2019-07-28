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


#include <sge/opencl/exception.hpp>
#include <sge/opencl/program/file_to_source_string_sequence.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::opencl::program::source_string_sequence
sge::opencl::program::file_to_source_string_sequence(
	boost::filesystem::path const &_path
)
{
	boost::filesystem::ifstream stream(
		_path
	);

	return
		sge::opencl::program::source_string_sequence{
			fcppt::optional::to_exception(
				fcppt::io::stream_to_string(
					stream
				),
				[
					&_path
				]{
					return
						sge::opencl::exception{
							FCPPT_TEXT("Failed to read ")
							+
							fcppt::filesystem::path_to_string(
								_path
							)
						};
				}
			)
		};
}
