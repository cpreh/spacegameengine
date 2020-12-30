//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/bytes_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/media/error_string.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/wave/extract_header.hpp>
#include <sge/wave/header.hpp>
#include <sge/wave/ignore_chunks_until.hpp>
#include <sge/wave/info.hpp>
#include <sge/wave/optional_header.hpp>
#include <sge/wave/optional_info.hpp>
#include <sge/wave/read_info.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/comparison.hpp>
#include <fcppt/endianness/format.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/apply.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::wave::optional_info
sge::wave::read_info(
	fcppt::log::object &_log,
	std::istream &_stream,
	sge::media::optional_name const &_name
)
{
	sge::wave::optional_header const riff(
		sge::wave::extract_header(
			_stream
		)
	);

	auto const compare_header_opt(
		[](
			sge::wave::optional_header const &_opt_header,
			sge::wave::header const &_expected
		)
		{
			return
				fcppt::optional::maybe(
					_opt_header,
					fcppt::const_(
						false
					),
					[
						&_expected
					](
						sge::wave::header const &_header
					)
					{
						return
							_header
							==
							_expected;
					}
				);
		}
	);

	bool const little_endian(
		compare_header_opt(
			riff,
			sge::wave::header{
				'R', 'I', 'F', 'F'
			}
		)
	);

	bool const big_endian(
		compare_header_opt(
			riff,
			sge::wave::header{
				'R', 'I', 'F', 'X'
			}
		)
	);

	if(
		!little_endian
		&&
		!big_endian
	)
	{
		return
			sge::wave::optional_info();
	}

	fcppt::endianness::format const endianness{
		little_endian
		?
			fcppt::endianness::format::little
		:
			fcppt::endianness::format::big
	};

	// throw away riff size
	fcppt::io::read<
		std::uint32_t
	>(
		_stream,
		endianness
	);

	if(
		!compare_header_opt(
			sge::wave::extract_header(
				_stream
			),
			sge::wave::header{
				'W','A','V','E'
			}
		)
	)
	{
		return
			sge::wave::optional_info();
	}

	if(
		!sge::wave::ignore_chunks_until(
			_log,
			_stream,
			sge::wave::header{
				'f','m','t',' '
			},
			endianness
		)
	)
	{
		return
			sge::wave::optional_info();
	}

	// ignore format chunk size
	fcppt::io::read<
		std::uint32_t
	>(
		_stream,
		endianness
	);

	if(
		fcppt::optional::maybe(
			fcppt::io::read<
				std::uint16_t
			>(
				_stream,
				endianness
			),
			fcppt::const_(
				true
			),
			[
				&_log,
				&_name
			](
				std::uint16_t const _format
			)
			{
				bool const unsupported{
					_format
					!=
					fcppt::literal<
						std::uint16_t
					>(
						1
					)
				};

				if(
					unsupported
				)
				{
					FCPPT_LOG_INFO(
						_log,
						fcppt::log::out
							<<
							sge::media::error_string(
								_name,
								FCPPT_TEXT("wave file is not pcm encoded!")
							)
							<<
							FCPPT_TEXT(" Format is ")
							<<
							_format
					)
				}

				return
					unsupported;
			}
		)
	)
	{
		return
			sge::wave::optional_info();
	}

	fcppt::optional::object<
		std::uint16_t
	> const channels(
		fcppt::io::read<
			std::uint16_t
		>(
			_stream,
			endianness
		)
	);

	fcppt::optional::object<
		std::uint32_t
	> const sample_rate(
		fcppt::io::read<
			std::uint32_t
		>(
			_stream,
			endianness
		)
	);

	// byte rate
	fcppt::io::read<
		std::uint32_t
	>(
		_stream,
		endianness
	);

	// block alignment
	fcppt::io::read<
		std::uint16_t
	>(
		_stream,
		endianness
	);

	fcppt::optional::object<
		std::uint16_t
	> const bits_per_sample(
		fcppt::io::read<
			std::uint16_t
		>(
			_stream,
			endianness
		)
	);

	if(
		!sge::wave::ignore_chunks_until(
			_log,
			_stream,
			sge::wave::header{
				'd','a','t','a'
			},
			endianness
		)
	)
	{
		return
			sge::wave::optional_info();
	}

	fcppt::optional::object<
		std::uint32_t
	> const data_size(
		fcppt::io::read<
			std::uint32_t
		>(
			_stream,
			endianness
		)
	);

	return
		fcppt::optional::apply(
			[
				endianness
			](
				std::uint16_t const _channels,
				std::uint32_t const _sample_rate,
				std::uint16_t const _bits_per_sample,
				std::uint32_t const _data_size
			)
			{
				sge::audio::channel_count const channels_result{
					fcppt::cast::size<
						sge::audio::channel_type
					>(
						_channels
					)
				};

				sge::audio::bits_per_sample const bits_per_sample_result{
					fcppt::cast::size<
						sge::audio::sample_count
					>(
						_bits_per_sample
					)
				};

				return
					sge::wave::info{
						endianness,
						channels_result,
						sge::audio::sample_rate{
							fcppt::cast::size<
								sge::audio::sample_count
							>(
								_sample_rate
							)
						},
						bits_per_sample_result,
						fcppt::cast::size<
							sge::audio::sample_count
						>(
							_data_size
						)
						/
						channels_result.get()
						/
						sge::audio::bytes_per_sample(
							bits_per_sample_result
						)
					};
			},
			channels,
			sample_rate,
			bits_per_sample,
			data_size
		);
}
