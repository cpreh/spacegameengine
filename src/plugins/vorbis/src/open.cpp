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


#include <sge/vorbis/callbacks.hpp>
#include <sge/vorbis/open.hpp>
#include <sge/vorbis/optional_stream_unique_ptr.hpp>
#include <sge/vorbis/stream.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/vorbisfile.h>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::vorbis::optional_stream_unique_ptr
sge::vorbis::open(
	std::istream &_stream
)
{
	OggVorbis_File ogg_file;

	int const result(
		::ov_open_callbacks(
			&_stream,
			&ogg_file,
			nullptr,
			0l,
			sge::vorbis::callbacks()
		)
	);

	return
		result
		==
		0
		?
			sge::vorbis::optional_stream_unique_ptr(
				fcppt::make_unique_ptr<
					sge::vorbis::stream
				>(
					ogg_file
				)
			)
		:
			sge::vorbis::optional_stream_unique_ptr()
		;
}
