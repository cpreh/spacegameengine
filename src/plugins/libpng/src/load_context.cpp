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


#include "../load_context.hpp"
#include "../header_bytes.hpp"
#include "../logger.hpp"
#include "../png.hpp"
#include "../to_sge_format.hpp"
#include <sge/image/file_exception.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/log/global.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <climits>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::libpng::load_context::load_context(
	std::istream &_stream,
	sge::image::optional_path const &_path
)
:
	context_base(
		_path
	),
	stream_(
		_stream
	),
	read_ptr_(
		PNG_LIBPNG_VER_STRING,
		static_cast<
			png_voidp
		>(
			this
		),
		&load_context::handle_error,
		&load_context::handle_warning
	),
	info_(
		read_ptr_.ptr()
	),
	dim_(),
	bytes_(),
	format_()
{
	png_set_sig_bytes(
		read_ptr_.ptr(),
		static_cast<
			png_size_t
		>(
			libpng::header_bytes::value
		)
	);

	png_set_read_fn(
		read_ptr_.ptr(),
		this,
		&load_context::handle_read);

	png_read_info(
		read_ptr_.ptr(),
		info_.get()
	);

	dim_ =
		image2d::dim(
			static_cast<
				image2d::dim::value_type
			>(
				png_get_image_width(
					read_ptr_.ptr(),
					info_.get()
				)
			),
			static_cast<
				image2d::dim::value_type
			>(
				png_get_image_height(
					read_ptr_.ptr(),
					info_.get()
				)
			)
		);

	png_byte const cs(
		png_get_channels(
			read_ptr_.ptr(),
			info_.get()
		)
	);

	png_byte const bpp(
		png_get_bit_depth(
			read_ptr_.ptr(),
			info_.get()
		)
	);

	png_uint_32 const color_type(
		png_get_color_type(
			read_ptr_.ptr(),
			info_.get()
		)
	);

	if(
		(bpp % CHAR_BIT) != 0
	)
		throw sge::image::file_exception(
			path_,
			FCPPT_TEXT("A png file has a bit depth that's not a multiple of a byte's size!")
		);

	FCPPT_LOG_DEBUG(
		libpng::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("png: dimensions: ")
			<< dim_
			<< FCPPT_TEXT(", bit depth: ")
			<< static_cast<unsigned>(bpp)
			<< FCPPT_TEXT(", channels: ")
			<< static_cast<unsigned>(cs)
	);

	if(
		color_type == PNG_COLOR_TYPE_PALETTE
	)
		throw sge::image::exception(
			FCPPT_TEXT("Palette images are not supported.")
		);
		// For some reason, this causes a crash, so this is disabled for now
		//png_set_palette_to_rgb(
		//	read_ptr_.ptr());
	else if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		if (bpp < 8)
			png_set_expand_gray_1_2_4_to_8(
				read_ptr_.ptr()
			);
	}

	if (
		png_get_valid(
			read_ptr_.ptr(),
			info_.get(),
			PNG_INFO_tRNS
		)
	)
		png_set_tRNS_to_alpha(
			read_ptr_.ptr()
		);

	if(bpp == 16)
		png_set_strip_16(
			read_ptr_.ptr());

	bytes_.resize_uninitialized(
		static_cast<
			byte_vector::size_type
		>(
			dim_.content()
			*
			(bpp / CHAR_BIT)
			* cs
		)
	);

	typedef fcppt::container::raw_vector<
		png_bytep
	> row_ptr_vector;

	row_ptr_vector row_ptrs(
		static_cast<row_ptr_vector::size_type>(
			dim_.h()));

	row_ptr_vector::size_type const stride(
		static_cast<
			row_ptr_vector::size_type
		>(
			cs * bpp/CHAR_BIT
		)
		* dim_.w()
	);

	for (row_ptr_vector::size_type i = 0; i < row_ptrs.size(); ++i)
		row_ptrs[i] = bytes_.data() + i * stride;

	png_read_image(
		read_ptr_.ptr(),
		row_ptrs.data());

	format_ = this->convert_format();
}
FCPPT_PP_POP_WARNING

sge::libpng::load_context::~load_context()
{
}

sge::image2d::dim const &
sge::libpng::load_context::dim() const
{
	return dim_;
}

sge::libpng::byte_vector &
sge::libpng::load_context::bytes()
{
	return bytes_;
}

sge::libpng::byte_vector const &
sge::libpng::load_context::bytes() const
{
	return bytes_;
}

sge::image::color::format::type
sge::libpng::load_context::format() const
{
	return format_;
}

void
sge::libpng::load_context::handle_read(
	png_structp read_ptr,
	png_bytep data,
	png_size_t length
)
{
	static_cast<load_context *>(png_get_io_ptr(read_ptr))->handle_read_impl(
		data,
		length);
}

void
sge::libpng::load_context::handle_read_impl(
	png_bytep _data,
	png_size_t _length
)
{
	stream_.read(
		reinterpret_cast<char *>(
			_data),
		static_cast<std::streamsize>(
			_length));
	if (stream_.gcount() < static_cast<std::streamsize>(_length))
		throw
			image::file_exception(
				path_,
				FCPPT_TEXT("didn't read as many bytes as supposed to"));
	if (!stream_)
		throw
			image::file_exception(
				path_,
				FCPPT_TEXT("reading failed"));
}

sge::image::color::format::type
sge::libpng::load_context::convert_format() const
{
	png_byte const depth(
		png_get_bit_depth(
			read_ptr_.ptr(),
			info_.get()
		)
	);

	sge::image::color::format::type const ret(
		libpng::to_sge_format(
			png_get_color_type(
				read_ptr_.ptr(),
				info_.get()
			),
			png_get_bit_depth(
				read_ptr_.ptr(),
				info_.get()
			)
		)
	);

	if(
		ret == sge::image::color::format::size
	)
		throw image::unsupported_format(
			path_,
			fcppt::insert_to_fcppt_string(
				static_cast<
					unsigned
				>(
					depth
				)
			)
			+
			FCPPT_TEXT(" bits per pixel")
		);

	return ret;
}
