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


#include <sge/image/file_exception.hpp>
#include <sge/image/optional_path.hpp>
#include <sge/libpng/load_context.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::libpng::load_context::load_context(
	std::istream &_stream,
	sge::image::optional_path const &_path,
	sge::libpng::read_ptr const &_read_ptr
)
:
	stream_(
		_stream
	),
	path_(
		_path
	)
{
	::png_set_read_fn(
		_read_ptr.ptr(),
		this,
		&sge::libpng::load_context::handle_read
	);
}

sge::libpng::load_context::~load_context()
{
}

void
sge::libpng::load_context::handle_read(
	png_structp const _read_ptr,
	png_bytep const _data,
	png_size_t const _length
)
{
	fcppt::cast::from_void_ptr<
		sge::libpng::load_context *
	>(
		::png_get_io_ptr(
			_read_ptr
		)
	)->handle_read_impl(
		_data,
		_length
	);
}

void
sge::libpng::load_context::handle_read_impl(
	png_bytep const _data,
	png_size_t const _length
)
{
	std::streamsize const signed_length(
		fcppt::cast::to_signed(
			_length
		)
	);

	if(
		!stream_.read(
			fcppt::cast::to_char_ptr<
				char *
			>(
				_data
			),
			signed_length
		)
	)
		throw
			sge::image::file_exception(
				path_,
				FCPPT_TEXT("reading failed")
			);

	if(
		stream_.gcount()
		<
		signed_length
	)
		throw
			sge::image::file_exception(
				path_,
				FCPPT_TEXT("didn't read as many bytes as supposed to")
			);
}
