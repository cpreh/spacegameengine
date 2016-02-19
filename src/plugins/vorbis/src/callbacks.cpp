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
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/vorbisfile.h>
#include <cerrno>
#include <cstddef>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace
{

std::istream &
get_stream(
	void *const _datasource
)
{
	return
		*fcppt::cast::from_void_ptr<
			std::istream *
		>(
			_datasource
		);
}

std::size_t
ogg_read(
	void *const _ptr,
	std::size_t const _size,
	std::size_t const _nmemb,
	void *const _datasource
)
{
	std::istream &stream(
		get_stream(
			_datasource
		)
	);

	if(
		stream.eof()
	)
		return
			0;

	stream.read(
		fcppt::cast::from_void_ptr<
			char *
		>(
			_ptr
		),
		fcppt::cast::size<
			std::streamsize
		>(
			fcppt::cast::to_signed(
				_size
				*
				_nmemb
			)
		)
	);

	if(
		// TODO: Is this correct?
		stream.bad()
	)
	{
		errno =
			EBADF;

		return
			0u;
	}

	return
		fcppt::cast::size<
			std::size_t
		>(
			fcppt::cast::to_unsigned(
				stream.gcount()
			)
		)
		/
		_size;
}

int
ogg_seek(
	void *const _datasource,
	ogg_int64_t const _offset,
	int const _whence
)
{
	std::istream &stream(
		get_stream(
			_datasource
		)
	);

	if(
		stream.eof()
	)
		stream.clear();

	stream.seekg(
		fcppt::cast::size<
			std::streamoff
		>(
			_offset
		),
		[
			_whence
		]{
			switch(
				_whence
			)
			{
			case SEEK_SET:
				return
					std::ios_base::beg;
			case SEEK_CUR:
				return
					std::ios_base::cur;
			case SEEK_END:
				return
					std::ios_base::end;
			}

			FCPPT_ASSERT_UNREACHABLE;
		}()
	);

	return
		0;
}

long
ogg_tell(
	void *const _datasource
)
{
	return
		fcppt::cast::size<
			long
		>(
			get_stream(
				_datasource
			).tellg()
		);
}

}

ov_callbacks
sge::vorbis::callbacks()
{
	ov_callbacks const callbacks = {
		&ogg_read,
		&ogg_seek,
		nullptr,
		&ogg_tell
	};

	return
		callbacks;
}
