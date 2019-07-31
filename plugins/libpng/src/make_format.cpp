//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/libpng/compare_gamma.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/gamma.hpp>
#include <sge/libpng/make_format.hpp>
#include <sge/libpng/optional_format.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/srgb_gamma.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>


sge::libpng::optional_format
sge::libpng::make_format(
	fcppt::log::object &_log,
	png_byte const _color_type,
	png_byte const _bit_depth,
	sge::libpng::gamma const _gamma
)
{
	// For now, we assume that all png images have a gamma of 2.2 (or
	// 0.45455 as a reciprocal), which indicates sRGB. If we have
	// sRGB, we return the corresponding format. The gamma value,
	// however, could be off, in which case we have to look further
	// into it and maybe return a different color format.
	if(
		!sge::libpng::compare_gamma(
			sge::libpng::srgb_gamma(),
			_gamma
		)
	)
	{
		FCPPT_LOG_ERROR(
			_log,
			fcppt::log::out
				<< FCPPT_TEXT("PNG file has gAMA ")
				<< _gamma
				<< FCPPT_TEXT(" which is not the expected sRGB gAMA of ")
				<< sge::libpng::srgb_gamma()
				<< FCPPT_TEXT('!')
		)

		return
			sge::libpng::optional_format();
	}

	if(
		_bit_depth
		!=
		8
	)
		return
			sge::libpng::optional_format();

	switch(
		_color_type
	)
	{
	case PNG_COLOR_TYPE_GRAY:
		return
			sge::libpng::optional_format(
				sge::libpng::format::l8
			);
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		return
			sge::libpng::optional_format(
				sge::libpng::format::la8
			);
	case PNG_COLOR_TYPE_PALETTE:
		break;
	case PNG_COLOR_TYPE_RGB:
		return
			sge::libpng::optional_format(
				sge::libpng::format::srgb8
			);
	case PNG_COLOR_TYPE_RGB_ALPHA:
		return
			sge::libpng::optional_format(
				sge::libpng::format::srgba8
			);
	}

	return
		sge::libpng::optional_format();
}
