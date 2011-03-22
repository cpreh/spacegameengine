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
#include <sge/image/file_exception.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image/exception.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional_impl.hpp>
#include <climits>
#include <iosfwd>

namespace
{
unsigned channels_from_format(
	sge::image::color::format::type const _format)
{
	switch (_format)
	{
		case sge::image::color::format::rgb8:
		case sge::image::color::format::rgb32f:
			return 3;
		case sge::image::color::format::alpha8:
			return 1;
		case sge::image::color::format::gray8:
			return 1;
		case sge::image::color::format::rgba8:
			return 4;
		case sge::image::color::format::argb8:
			return 4;
		case sge::image::color::format::bgra8:
			return PNG_TRANSFORM_BGR;
		case sge::image::color::format::rgba32f:
		case sge::image::color::format::argb32f:
		case sge::image::color::format::bgra32f:
			return 4;
		case sge::image::color::format::size: break;
	}

	throw sge::image::exception(FCPPT_TEXT("unknown color format, please maintain this crap"));
}

int transforms_from_format(
	fcppt::filesystem::path const &_path,
	sge::image::color::format::type const _format)
{
	switch (_format)
	{
		case sge::image::color::format::alpha8:
			throw
				sge::image::unsupported_format(
					_path,
					FCPPT_TEXT("alpha8")
				);
		case sge::image::color::format::gray8:
		case sge::image::color::format::rgba8:
		case sge::image::color::format::rgb8:
			return PNG_TRANSFORM_IDENTITY;
		case sge::image::color::format::argb8:
			return PNG_TRANSFORM_SWAP_ALPHA;
		case sge::image::color::format::bgra8:
			return PNG_TRANSFORM_BGR;
		case sge::image::color::format::rgba32f:
		case sge::image::color::format::argb32f:
		case sge::image::color::format::bgra32f:
		case sge::image::color::format::rgb32f:
			throw
				sge::image::unsupported_format(
					_path,
					FCPPT_TEXT("{r,g,b,a}32f")
				);
		case sge::image::color::format::size: break;
	}

	throw sge::image::exception(FCPPT_TEXT("unknown color format, please maintain this crap"));
}

int bit_depth_from_format(
	fcppt::filesystem::path const &_path,
	sge::image::color::format::type const _format)
{
	switch (_format)
	{
		case sge::image::color::format::alpha8:
		case sge::image::color::format::gray8:
		case sge::image::color::format::rgba8:
		case sge::image::color::format::argb8:
		case sge::image::color::format::bgra8:
		case sge::image::color::format::rgb8:
			return 8;
		case sge::image::color::format::rgba32f:
		case sge::image::color::format::argb32f:
		case sge::image::color::format::bgra32f:
		case sge::image::color::format::rgb32f:
			throw
				sge::image::unsupported_format(
					_path,
					FCPPT_TEXT("{r,g,b,a}32f"));
		case sge::image::color::format::size: break;
	}
	throw
		sge::image::file_exception(
			_path,
			FCPPT_TEXT("unknown color format, please maintain this crap"));
}

int color_type_from_format(
	fcppt::filesystem::path const &_path,
	sge::image::color::format::type const _format)
{
	switch (_format)
	{
		case sge::image::color::format::alpha8:
			throw
				sge::image::unsupported_format(
					_path,
					FCPPT_TEXT("alpha8"));
		case sge::image::color::format::gray8:
			return PNG_COLOR_TYPE_GRAY;
		case sge::image::color::format::rgba8:
		case sge::image::color::format::argb8:
		case sge::image::color::format::bgra8:
			return PNG_COLOR_TYPE_RGB_ALPHA;
		case sge::image::color::format::rgb8:
			return PNG_COLOR_TYPE_RGB;
		case sge::image::color::format::rgba32f:
		case sge::image::color::format::argb32f:
		case sge::image::color::format::bgra32f:
		case sge::image::color::format::rgb32f:
			throw
				sge::image::unsupported_format(
					_path,
					FCPPT_TEXT("{r,g,b,a}32f"));
		case sge::image::color::format::size: break;
	}

	throw sge::image::exception(FCPPT_TEXT("unknown color format, please maintain this crap"));
}
}

sge::libpng::write_context::write_context(
	fcppt::filesystem::path const &_path,
	image2d::dim const &_dim,
	byte_vector &_bytes,
	image::color::format::type const _format)
:
	context_base(
		_path),
	file_(
		_path),
	bytes_(
		_bytes),
	format_(
		_format),
	write_ptr_(
		png_create_write_struct(
			PNG_LIBPNG_VER_STRING,
			static_cast<png_voidp>(
				this),
			&write_context::handle_error,
			&write_context::handle_warning))
{
	if (!file_.is_open())
		throw
			image::file_exception(
				_path,
				FCPPT_TEXT("couldn't open file"));

	png_set_write_fn(
		write_ptr_.ptr(),
		static_cast<png_voidp>(
			this),
		&write_context::handle_write,
		&write_context::handle_flush);

	png_set_IHDR(
		write_ptr_.ptr(),
		write_ptr_.info(),
		static_cast<png_uint_32>(
			_dim.w()),
		static_cast<png_uint_32>(
			_dim.h()),
		bit_depth_from_format(
			*path_,
			_format),
		color_type_from_format(
			*path_,
			_format),
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);

	png_write_info(
		write_ptr_.ptr(),
		write_ptr_.info());

	typedef fcppt::container::raw_vector<png_bytep> row_ptr_vector;

	row_ptr_vector row_ptrs(
		static_cast<row_ptr_vector::size_type>(
			_dim.h()));

	row_ptr_vector::size_type const stride =
		channels_from_format(_format) * bit_depth_from_format(*path_,_format)/CHAR_BIT * _dim.w();

	for (row_ptr_vector::size_type i = 0; i < row_ptrs.size(); ++i)
		row_ptrs[i] = bytes_.data() + i * stride;

	png_write_image(
		write_ptr_.ptr(),
		row_ptrs.data());

	png_write_end(
		write_ptr_.ptr(),
		write_ptr_.info());
}

void sge::libpng::write_context::handle_write(
	png_structp const _ptr,
	png_bytep _data,
	png_size_t const _length)
{
	static_cast<write_context *>(png_get_io_ptr(_ptr))->handle_write_impl(
		_data,
		_length);
}

void sge::libpng::write_context::handle_write_impl(
	png_bytep _data,
	png_size_t const _length)
{
	file_.write(
		reinterpret_cast<char const*>(
			_data),
		static_cast<std::streamsize>(
			_length));
	if (!file_)
		throw image::file_exception(
			path_,
			FCPPT_TEXT("error writing"));
}

void sge::libpng::write_context::handle_flush(
	png_structp const _ptr)
{
	static_cast<write_context *>(png_get_io_ptr(_ptr))->handle_flush_impl();
}

void sge::libpng::write_context::handle_flush_impl()
{
	file_.flush();
}
