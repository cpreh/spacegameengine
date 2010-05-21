/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "../load_context.hpp"
#include <sge/image/file_exception.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <climits>
#include <cstddef>

std::size_t const sge::libpng::load_context::header_bytes_ =
	static_cast<std::size_t>(8);

sge::libpng::load_context::load_context(
	fcppt::filesystem::path const &_path)
:
	context_base(
		_path),
	file_(
		_path),
	read_ptr_(),
	dim_(),
	bytes_(),
	format_()
{
	if (!file_.is_open())
		throw
			image::file_exception(
				_path,
				FCPPT_TEXT("couldn't open file"));

	if (!is_png())
		throw
			image::unsupported_format(
				_path,
				FCPPT_TEXT("not a png file")
			);

	read_ptr_.reset(
		new read_ptr(
			png_create_read_struct(
				PNG_LIBPNG_VER_STRING,
				static_cast<png_voidp>(
					this),
				&load_context::handle_error,
				&load_context::handle_warning)));

	png_set_sig_bytes(
		read_ptr_->ptr(),
		static_cast<png_size_t>(
			header_bytes_));

	png_set_read_fn(
		read_ptr_->ptr(),
	  this,
		&load_context::handle_read);

	png_read_info(
		read_ptr_->ptr(),
		read_ptr_->info());

	dim_ = image::dim_type(
		static_cast<image::dim_type::value_type>(
			png_get_image_width(
				read_ptr_->ptr(),
				read_ptr_->info())),
		static_cast<image::dim_type::value_type>(
			png_get_image_height(
				read_ptr_->ptr(),
				read_ptr_->info())));

	png_byte const cs =
		png_get_channels(
			read_ptr_->ptr(),
			read_ptr_->info());
	png_byte const bpp =
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	png_uint_32 const color_type =
		png_get_color_type(
			read_ptr_->ptr(),
			read_ptr_->info());
	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_ << FCPPT_TEXT("png: dimensions: ") << dim_);
	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_ << FCPPT_TEXT("png: bit depth: ") << static_cast<int>(bpp));
	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_ << FCPPT_TEXT("png: channels: ") << static_cast<int>(cs));

	if (color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_palette_to_rgb(
			read_ptr_->ptr());
	}
	else if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		if (bpp < 8)
			png_set_expand_gray_1_2_4_to_8(
				read_ptr_->ptr());
	}

	if (png_get_valid(read_ptr_->ptr(),read_ptr_->info(), PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(
			read_ptr_->ptr());

	if (bpp == 16)
		png_set_strip_16(
			read_ptr_->ptr());

	bytes_.reserve(
		static_cast<byte_vector::size_type>(
			dim_.content()*(bpp/CHAR_BIT)*cs));

	typedef fcppt::container::raw_vector<png_bytep> row_ptr_vector;

	row_ptr_vector row_ptrs(
		static_cast<row_ptr_vector::size_type>(
			dim_.h()));

	row_ptr_vector::size_type const stride =
		cs * bpp/CHAR_BIT * dim_.w();

	for (row_ptr_vector::size_type i = 0; i < row_ptrs.size(); ++i)
		row_ptrs[i] = bytes_.data() + i * stride;

	png_read_image(
		read_ptr_->ptr(),
		row_ptrs.data());

	format_ = convert_format();
}

sge::image::dim_type const &sge::libpng::load_context::dim() const
{
	return dim_;
}

sge::libpng::byte_vector &sge::libpng::load_context::bytes()
{
	return bytes_;
}

sge::libpng::byte_vector const &sge::libpng::load_context::bytes() const
{
	return bytes_;
}

sge::image::color::format::type sge::libpng::load_context::format() const
{
	return format_;
}

bool sge::libpng::load_context::is_png()
{
	char buf[header_bytes_];

	file_.read(
		buf,
		static_cast<std::streamsize>(
			header_bytes_));

	if (file_.gcount() < static_cast<std::streamsize>(header_bytes_))
		return false;

	return
		!png_sig_cmp(
			reinterpret_cast<png_byte *>(
				buf),
			static_cast<png_size_t>(
				0),
			static_cast<png_size_t>(
				header_bytes_));
}

void sge::libpng::load_context::handle_read(
	png_structp read_ptr,
	png_bytep data,
	png_size_t length)
{
	static_cast<load_context *>(png_get_io_ptr(read_ptr))->handle_read_impl(
		data,
		length);
}

void sge::libpng::load_context::handle_read_impl(
	png_bytep _data,
	png_size_t _length)
{
	file_.read(
		reinterpret_cast<char *>(
			_data),
		static_cast<std::streamsize>(
			_length));
	if (file_.gcount() < static_cast<std::streamsize>(_length))
		throw
			image::file_exception(
				path_,
				FCPPT_TEXT("didn't read as many bytes as supposed to"));
	if (!file_)
		throw
			image::file_exception(
				path_,
				FCPPT_TEXT("reading failed"));
}

sge::image::color::format::type sge::libpng::load_context::convert_format() const
{
	switch(
		png_get_color_type(
			read_ptr_->ptr(),
			read_ptr_->info()))
	{
		case PNG_COLOR_TYPE_GRAY:
			return convert_gray_format();
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			throw image::unsupported_format(path_,FCPPT_TEXT("gray alpha"));
		break;
		case PNG_COLOR_TYPE_PALETTE:
			throw image::unsupported_format(path_,FCPPT_TEXT("palette"));
		case PNG_COLOR_TYPE_RGB:
			return convert_rgb_format();
		case PNG_COLOR_TYPE_RGB_ALPHA:
			return convert_rgba_format();
	}
	throw image::unsupported_format(path_,FCPPT_TEXT("unknown format"));
}

sge::image::color::format::type sge::libpng::load_context::convert_gray_format() const
{
	png_byte const depth =
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	if (depth != 8)
		throw image::unsupported_format(path_,FCPPT_TEXT("gray, ")+fcppt::lexical_cast<fcppt::string>(depth)+FCPPT_TEXT(" bits per pixel"));
	return sge::image::color::format::gray8;
}

sge::image::color::format::type sge::libpng::load_context::convert_rgb_format() const
{
	png_byte const depth =
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	throw image::unsupported_format(path_,FCPPT_TEXT("rgb, ")+fcppt::lexical_cast<fcppt::string>(static_cast<unsigned>(depth))+FCPPT_TEXT(" bits"));
}

sge::image::color::format::type sge::libpng::load_context::convert_rgba_format() const
{
	png_byte const depth =
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	if (depth != 8)
		throw image::unsupported_format(path_,FCPPT_TEXT("rgb, ")+fcppt::lexical_cast<fcppt::string>(static_cast<unsigned>(depth))+FCPPT_TEXT(" bits"));
	return sge::image::color::format::rgba8;
}
