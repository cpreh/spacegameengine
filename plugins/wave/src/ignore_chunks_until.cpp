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


#include <sge/wave/extract_header.hpp>
#include <sge/wave/header.hpp>
#include <sge/wave/ignore_chunks_until.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <fcppt/config/external_end.hpp>


bool
sge::wave::ignore_chunks_until(
	fcppt::log::object &_log,
	std::istream &_stream,
	sge::wave::header const &_header,
	fcppt::endianness::format const _endianness
)
{
	while(
		fcppt::optional::maybe(
			sge::wave::extract_header(
				_stream
			),
			fcppt::const_(
				false
			),
			[
				&_log,
				&_header
			](
				sge::wave::header const &_cur
			)
			{
				bool const do_continue{
					_header
					!=
					_cur
				};

				if(
					do_continue
				)
					FCPPT_LOG_INFO(
						_log,
						fcppt::log::_
							<<
							FCPPT_TEXT("detected unknown subchunk ")
							<<
							fcppt::from_std_string(
								std::string(
									_cur.begin(),
									_cur.end()
								)
							)
					);

				return
					do_continue;
			}
		)
	)
	{
		if(
			fcppt::optional::maybe(
				fcppt::io::read<
					std::uint32_t
				>(
					_stream,
					_endianness
				),
				fcppt::const_(
					true
				),
				[
					&_stream
				](
					std::uint32_t const _chunk_size
				)
				{
					_stream.seekg(
						fcppt::cast::size<
							std::streamoff
						>(
							fcppt::cast::to_signed(
								_chunk_size
							)
						),
						std::ios_base::cur
					);

					return
						false;
				}
			)
		)
			return
				false;
	}

	return
		_stream.good();
}
