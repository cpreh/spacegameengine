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


#ifndef SGE_GUI_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_CHANNEL_BLITTER_HPP_INCLUDED

#include "../../utility/normalization.hpp"
#include <boost/type_traits/remove_const.hpp>

namespace sge
{
namespace gui
{
namespace utility
{

template<
	class DstPixel,
	class FontPixel
>
class font_channel_blitter 
{
public:
	typedef void result_type;

	typedef typename DstPixel::layout::channel_type channel_type;

	typedef typename FontPixel::layout::channel_type font_channel_type;

	font_channel_blitter(
		DstPixel const &bgcolor,
		DstPixel const &fontcolor,
		FontPixel const &font,
		DstPixel &result);

	template<
		class T
	>
	result_type
	operator()(
		T &
	) const;

	result_type
	operator()(
		mizuiro::color::channel::alpha &
	) const;
private:
	DstPixel const &bgcolor,fontcolor;
	FontPixel const &font;
	DstPixel &result;
};

}
}
}

template<
	class DstPixel,
	class FontPixel
>
sge::gui::utility::font_channel_blitter<DstPixel,FontPixel>::font_channel_blitter(
	DstPixel const &bgcolor,
	DstPixel const &fontcolor,
	FontPixel const &font,
	DstPixel &result)
:
	bgcolor(bgcolor),
	fontcolor(fontcolor),
	font(font),
	result(result)
{}


template<
	class DstPixel,
	class FontPixel
>
template<
	class T
>
typename sge::gui::utility::font_channel_blitter<DstPixel, FontPixel>::result_type
sge::gui::utility::font_channel_blitter<DstPixel,FontPixel>::operator()(
	T &t
) const
{
	// FIXME: add range value, divide by max-min (for font_channel_type and channel_type)
	float const font_value = normalize<float>(font[0]);

	result. template set<T>(
		static_cast<channel_type>(
			static_cast<float>(fontcolor. template get<T>()) * font_value
			+ static_cast<float>(bgcolor. template get<T>())
		)
		* (1.0f - font_value)
	);
}

template<
	class DstPixel,
	class FontPixel
>
typename sge::gui::utility::font_channel_blitter<DstPixel, FontPixel>::result_type
sge::gui::utility::font_channel_blitter<DstPixel,FontPixel>::operator()(
	mizuiro::color::channel::alpha &
) const
{
	float const font_value = normalize<float>(font[0]);

	result. template set<
		mizuiro::color::channel::alpha
	>( 
		denormalize<channel_type>(
			std::min(
				normalize<
					float
				>(
					bgcolor. template get<
						mizuiro::color::channel::alpha
					>()
				)
				+ static_cast<
					float
				>(
					font_value
				),
				1.0f
			)
		)
	);
}

#endif
