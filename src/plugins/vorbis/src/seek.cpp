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
#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/error_string.hpp>
#include <sge/vorbis/seek.hpp>
#include <sge/vorbis/stream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <fcppt/config/external_end.hpp>


void
sge::vorbis::seek(
	sge::vorbis::stream &_stream,
	sge::media::optional_name const &_name,
	ogg_int64_t const _pos
)
{
	int const error{
		::ov_pcm_seek(
			_stream.get(),
			_pos
		)
	};

	if(
		error
		!=
		0
	)
		throw
			sge::audio::file_exception{
				_name,
				FCPPT_TEXT("vorbis: couldn't reset file: ")
				+
				sge::vorbis::error_string(
					error
				)
			};
}
