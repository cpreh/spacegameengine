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
#include <sge/renderer/color_convert.hpp>
#include <sge/renderer/any_color_convert.hpp>
#include <boost/mpl/for_each.hpp>

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
	: font_color(font_color)
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
	boost::mpl::for_each<typename Dst::layout_t::channel_mapping_t>(
		font_channel_blitter<Dst,Font>(
			renderer::color_convert<Dst>(src_color),
			renderer::any_color_convert<Dst>(font_color),
			font_value,
			result));
}

#endif
