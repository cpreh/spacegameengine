//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <ios>
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
						fcppt::log::out
							<<
							FCPPT_TEXT("detected unknown subchunk ")
							<<
							fcppt::from_std_string(
								std::string(
									_cur.begin(),
									_cur.end()
								)
							)
					)

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
