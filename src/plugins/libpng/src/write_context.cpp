/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_context.hpp>
#include <sge/libpng/write_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


sge::libpng::write_context::write_context(
	boost::filesystem::path const &_path,
	std::ostream &_stream,
	sge::libpng::write_ptr const &_write_ptr
)
:
	path_(
		_path
	),
	stream_(
		_stream
	)
{
	::png_set_write_fn(
		_write_ptr.ptr(),
		this,
		&sge::libpng::write_context::handle_write,
		&sge::libpng::write_context::handle_flush
	);
}

sge::libpng::write_context::~write_context()
{
}

void
sge::libpng::write_context::handle_write(
	png_structp const _ptr,
	png_bytep const _data,
	png_size_t const _length
)
{
	sge::libpng::write_context::get_instance(
		_ptr
	).handle_write_impl(
		_data,
		_length
	);
}

void
sge::libpng::write_context::handle_write_impl(
	png_bytep const _data,
	png_size_t const _length
)
{
	stream_.write(
		fcppt::cast::to_char_ptr<
			char const *
		>(
			_data
		),
		fcppt::cast::to_signed(
			_length
		)
	);

	if(
		!stream_
	)
		throw
			sge::image::file_exception(
				sge::image::optional_path(
					path_
				),
				FCPPT_TEXT("error writing")
			);
}

void
sge::libpng::write_context::handle_flush(
	png_structp const _ptr
)
{
	sge::libpng::write_context::get_instance(
		_ptr
	).handle_flush_impl();
}

void
sge::libpng::write_context::handle_flush_impl()
{
	stream_.flush();
}

sge::libpng::write_context &
sge::libpng::write_context::get_instance(
	png_structp const _ptr
)
{
	return
		*fcppt::cast::from_void_ptr<
			sge::libpng::write_context *
		>(
			::png_get_io_ptr(
				_ptr
			)
		);
}
