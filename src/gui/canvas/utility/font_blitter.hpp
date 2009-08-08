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


#ifndef SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED
#define SGE_GUI_UTILITY_FONT_BLITTER_HPP_INCLUDED

#include "font_channel_blitter.hpp"
#include <sge/image/color/convert.hpp>
#include <sge/image/color/any/convert.hpp>
#include <mizuiro/color/for_each_channel.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
class font_blitter
{
	public:
	explicit font_blitter(
		color const &font_color);

	template<
		typename Font,
		typename Src,
		typename Dst
	>
	void operator()(
		Font const &font_value,
		Src const &src_color,
		Dst &dst_color) const;
	
	private:
	color const font_color;
};
}
}
}

sge::gui::utility::font_blitter::font_blitter(
	color const &font_color)
:
	font_color(font_color)
{
}

template<
	typename Font,
	typename Src,
	typename Dst
>
void
sge::gui::utility::font_blitter::operator()(
	Font const &font_value,
	Src const &src_color,
	Dst &result) const
{
	mizuiro::color::for_each_channel<
		typename Dst::layout
	>(
		font_channel_blitter<
			// TODO: create a function for this like std::make_pair!
			mizuiro::color::object<
				typename Dst::layout
			>,
			Dst,
			Font
		>(
			image::color::convert<
				typename Dst::layout
			>(
				src_color
			),
			image::color::any::convert<
				typename Dst::layout
			>(
				font_color
			),
			font_value,
			result
		)
	);
}

#endif
