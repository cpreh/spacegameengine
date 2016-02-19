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


#include <sge/audio/file_exception.hpp>
#include <sge/audio/raw_pointer.hpp>
#include <sge/media/error_string.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/logger.hpp>
#include <sge/vorbis/read.hpp>
#include <sge/vorbis/stream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/endianness/is_little_endian.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <fcppt/config/external_end.hpp>


std::size_t
sge::vorbis::read(
	sge::vorbis::stream &_stream,
	sge::media::optional_name const &_name,
	sge::audio::raw_pointer const _data,
	std::size_t const _size
)
{
	int bitstream;

	long const result(
		::ov_read(
			_stream.get(),
			fcppt::cast::to_char_ptr<
				char *
			>(
				_data
			),
			fcppt::cast::size<
				int
			>(
				fcppt::cast::to_signed(
					_size
				)
			),
			fcppt::endianness::is_little_endian()
			?
				0
			:
				1
			,
			2, // 8 or 16 bit samples
			1, // 0 is unsigned data, 1 is signed
			&bitstream
		)
	);

	switch(
		result
	)
	{
	// When reading from the file, you might encounter a bad fragment
	// which is indicated by OV_HOLE. According to a mailing list post,
	// we can just ignore holes.
	case OV_HOLE:
		FCPPT_LOG_WARNING(
			sge::vorbis::logger(),
			fcppt::log::_ <<
				sge::media::error_string(
					_name,
					FCPPT_TEXT("Encountered corrupt vorbis data.")
				)
		);
		break;
	case OV_EBADLINK:
		throw
			sge::audio::file_exception{
				_name,
				FCPPT_TEXT("An invalid stream section was supplied to libvorbisfile, or the requested link is corrupt.")
			};
	case OV_EINVAL:
		throw
			sge::audio::file_exception{
				_name,
				FCPPT_TEXT("The initial file headers couldn't be read or are corrupt, or the initial open call for vf failed.")
			};
	}

	if(
		result
		==
		0l
	)
	{
		FCPPT_LOG_DEBUG(
			sge::vorbis::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Read until the end.")
		);
	}

	return
		fcppt::cast::to_unsigned(
			result
		);
}
