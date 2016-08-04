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


#include <sge/log/default_level_streams.hpp>
#include <sge/log/stream.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/level_stream.hpp>
#include <fcppt/log/level_stream_array.hpp>
#include <fcppt/log/format/default_level.hpp>
#include <fcppt/log/format/optional_function.hpp>


fcppt::log::level_stream_array
sge::log::default_level_streams()
{
	return
		fcppt::algorithm::enum_array_init<
			fcppt::log::level_stream_array
		>(
			[](
				fcppt::log::level const _level
			)
			{
				return
					fcppt::log::level_stream(
						sge::log::stream(),
						fcppt::log::format::optional_function(
							fcppt::log::format::default_level(
								_level
							)
						)
					);
			}
		);
}
