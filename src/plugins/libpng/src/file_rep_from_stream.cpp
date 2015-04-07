/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image2d/dim.hpp>
#include <sge/image2d/file_exception.hpp>
#include <sge/image2d/unsupported_format.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/bytes_per_pixel.hpp>
#include <sge/libpng/error_context.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/file_rep_from_stream.hpp>
#include <sge/libpng/get_gamma.hpp>
#include <sge/libpng/header_bytes.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/load_context.hpp>
#include <sge/libpng/logger.hpp>
#include <sge/libpng/make_format.hpp>
#include <sge/libpng/make_row_vector.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <sge/libpng/row_vector.hpp>
#include <sge/media/optional_path_fwd.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/promote.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <climits>
#include <iosfwd>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::file_rep
sge::libpng::file_rep_from_stream(
	std::istream &_stream,
	sge::media::optional_path const &_path
)
{
	sge::libpng::error_context error_context(
		_path
	);

	sge::libpng::read_ptr const read_ptr(
		error_context
	);

	sge::libpng::info const info(
		read_ptr.ptr()
	);

	::png_set_sig_bytes(
		read_ptr.ptr(),
		sge::libpng::header_bytes::value
	);

	sge::libpng::load_context load_context(
		_stream,
		_path,
		read_ptr
	);

	::png_read_info(
		read_ptr.ptr(),
		info.get()
	);

	sge::image2d::dim const size(
		::png_get_image_width(
			read_ptr.ptr(),
			info.get()
		),
		::png_get_image_height(
			read_ptr.ptr(),
			info.get()
		)
	);

	png_byte const channels(
		::png_get_channels(
			read_ptr.ptr(),
			info.get()
		)
	);

	png_byte const bpp(
		::png_get_bit_depth(
			read_ptr.ptr(),
			info.get()
		)
	);

	png_byte const color_type(
		::png_get_color_type(
			read_ptr.ptr(),
			info.get()
		)
	);

	if(
		(bpp % CHAR_BIT) != 0
	)
		throw
			sge::image2d::file_exception(
				_path,
				FCPPT_TEXT("A png file has a bit depth that's not a multiple of a byte's size!")
			);

	FCPPT_LOG_DEBUG(
		sge::libpng::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("png: dimensions: ")
			<< size
			<< FCPPT_TEXT(", bit depth: ")
			<< fcppt::cast::promote(
				bpp
			)
			<< FCPPT_TEXT(", channels: ")
			<< fcppt::cast::promote(
				channels
			)
	);

	switch(
		color_type
	)
	{
		case PNG_COLOR_TYPE_PALETTE:
			throw
				sge::image2d::unsupported_format(
					_path,
					FCPPT_TEXT("Palette images are not supported.")
				);
		case PNG_COLOR_TYPE_GRAY:
			if(
				bpp < 8
			)
				::png_set_expand_gray_1_2_4_to_8(
					read_ptr.ptr()
				);
			break;
	}

	if(
		::png_get_valid(
			read_ptr.ptr(),
			info.get(),
			PNG_INFO_tRNS
		)
	)
		::png_set_tRNS_to_alpha(
			read_ptr.ptr()
		);

	if(
		bpp
		==
		16
	)
		::png_set_strip_16(
			read_ptr.ptr()
		);

	sge::libpng::bytes_per_pixel const bytes_per_pixel(
		fcppt::cast::to_unsigned(
			(bpp / CHAR_BIT)
			* channels
		)
	);

	sge::libpng::byte_vector bytes(
		size.content()
		*
		bytes_per_pixel.get()
	);

	sge::libpng::row_vector row_ptrs(
		sge::libpng::make_row_vector(
			size,
			bytes.data(),
			bytes_per_pixel
		)
	);

	::png_read_image(
		read_ptr.ptr(),
		row_ptrs.data()
	);

	return
		sge::libpng::file_rep(
			size,
			fcppt::optional_to_exception(
				sge::libpng::make_format(
					color_type,
					bpp,
					sge::libpng::get_gamma(
						read_ptr,
						info
					)
				),
				[
					&_path,
					bpp
				]{
					return
						sge::image2d::unsupported_format(
							_path,
							fcppt::insert_to_fcppt_string(
								fcppt::cast::promote(
									bpp
								)
							)
							+
							FCPPT_TEXT(" bits per pixel")
						);
				}
			),
			std::move(
				bytes
			)
		);
}
