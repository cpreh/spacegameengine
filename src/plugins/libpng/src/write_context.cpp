/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../write_context.hpp"
#include "../bit_depth_from_format.hpp"
#include "../color_type_from_format.hpp"
#include "../png.hpp"
#include "../transforms_from_format.hpp"
#include <sge/image/color/element_count.hpp>
#include <sge/image/file_exception.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <climits>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::libpng::write_context::write_context(
	fcppt::filesystem::path const &_path,
	image2d::dim const &_dim,
	byte_vector &_bytes,
	image::color::format::type const _format
)
:
	context_base(
		_path
	),
	file_(
		_path
	),
	bytes_(
		_bytes
	),
	format_(
		_format
	),
	write_ptr_(
		PNG_LIBPNG_VER_STRING,
		static_cast<
			png_voidp
		>(
			this
		),
		&write_context::handle_error,
		&write_context::handle_warning
	),
	info_(
		write_ptr_.ptr()
	)
{
	if(
		!file_.is_open()
	)
		throw
			image::file_exception(
				_path,
				FCPPT_TEXT("couldn't open file")
			);

	png_set_write_fn(
		write_ptr_.ptr(),
		static_cast<png_voidp>(
			this),
		&write_context::handle_write,
		&write_context::handle_flush);

	png_set_IHDR(
		write_ptr_.ptr(),
		info_.get(),
		static_cast<
			png_uint_32
		>(
			_dim.w()
		),
		static_cast<
			png_uint_32
		>(
			_dim.h()
		),
		libpng::bit_depth_from_format(
			*path_,
			_format
		),
		libpng::color_type_from_format(
			*path_,
			_format
		),
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);

	png_write_info(
		write_ptr_.ptr(),
		info_.get());

	typedef fcppt::container::raw_vector<png_bytep> row_ptr_vector;

	row_ptr_vector row_ptrs(
		static_cast<row_ptr_vector::size_type>(
			_dim.h()));

	row_ptr_vector::size_type const stride(
		sge::image::color::element_count(
			_format
		)
		*
		static_cast<
			sge::image::size_type
		>(
			libpng::bit_depth_from_format(
				*path_,
				_format
			)
		)
		/
		CHAR_BIT
		* _dim.w()
	);

	for (row_ptr_vector::size_type i = 0; i < row_ptrs.size(); ++i)
		row_ptrs[i] = bytes_.data() + i * stride;

	png_write_image(
		write_ptr_.ptr(),
		row_ptrs.data());

	png_write_end(
		write_ptr_.ptr(),
		info_.get());
}
FCPPT_PP_POP_WARNING

sge::libpng::write_context::~write_context()
{
}

void
sge::libpng::write_context::handle_write(
	png_structp const _ptr,
	png_bytep _data,
	png_size_t const _length)
{
	static_cast<
		write_context *
	>(
		png_get_io_ptr(
			_ptr
		)
	)->handle_write_impl(
		_data,
		_length
	);
}

void
sge::libpng::write_context::handle_write_impl(
	png_bytep _data,
	png_size_t const _length
)
{
	file_.write(
		reinterpret_cast<
			char const *
		>(
			_data
		),
		static_cast<
			std::streamsize
		>(
			_length
		)
	);

	if(
		!file_
	)
		throw image::file_exception(
			path_,
			FCPPT_TEXT("error writing")
		);
}

void
sge::libpng::write_context::handle_flush(
	png_structp const _ptr
)
{
	static_cast<
		write_context *
	>(
		png_get_io_ptr(
			_ptr
		)
	)->handle_flush_impl();
}

void
sge::libpng::write_context::handle_flush_impl()
{
	file_.flush();
}
