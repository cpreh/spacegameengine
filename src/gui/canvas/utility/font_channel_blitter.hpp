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
	typename Source1,
	typename DstPixel,
	typename FontPixel
>
class font_channel_blitter 
{
public:
	typedef void result_type;

	typedef typename DstPixel::layout::channel_type channel_type;

	typedef typename FontPixel::layout::channel_type font_channel_type;

	font_channel_blitter(
		Source1 const &fontcolor,
		FontPixel const &font,
		DstPixel &result
	);

	template<
		typename Channel
	>
	result_type
	operator()(
		Channel &
	) const;

	result_type
	operator()(
		mizuiro::color::channel::alpha &
	) const;
private:
	Source1 const fontcolor;
	
	FontPixel const font;

	DstPixel &result;
};

}
}
}

template<
	typename Source1,
	typename DstPixel,
	typename FontPixel
>
sge::gui::utility::font_channel_blitter<
	Source1,
	DstPixel,
	FontPixel
>::font_channel_blitter(
	Source1 const &fontcolor,
	FontPixel const &font,
	DstPixel &result
)
:
	fontcolor(fontcolor),
	font(font),
	result(result)
{}


template<
	typename Source1,
	typename DstPixel,
	typename FontPixel
>
template<
	typename Channel
>
typename sge::gui::utility::font_channel_blitter<
	Source1,
	DstPixel,
	FontPixel
>::result_type
sge::gui::utility::font_channel_blitter<
	Source1,
	DstPixel,
	FontPixel
>::operator()(
	Channel &
) const
{
	/*
	// FIXME: add range value, divide by max-min (for font_channel_type and channel_type)
	float const font_value = normalize<float>(font[0]);

	result. template set<T>(
		static_cast<channel_type>(
			static_cast<float>(fontcolor. template get<T>()) * font_value
			+ static_cast<float>(bgcolor. template get<T>())
		)
		* (1.0f - font_value)
	);
	*/
}

template<
	typename Source1,
	typename DstPixel,
	typename FontPixel
>
typename sge::gui::utility::font_channel_blitter<
	Source1,
	DstPixel,
	FontPixel
>::result_type
sge::gui::utility::font_channel_blitter<
	Source1,
	DstPixel,
	FontPixel
>::operator()(
	mizuiro::color::channel::alpha &
) const
{
	/*
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
	*/
}

#endif
