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


#ifndef SGE_GUI_UTILITY_SET_PIXEL_HPP_INCLUDED
#define SGE_GUI_UTILITY_SET_PIXEL_HPP_INCLUDED

#include <sge/gui/types.hpp>
#include <sge/renderer/any_color_convert.hpp>

namespace sge
{
namespace gui
{
namespace utility
{

class set_pixel {
public:
	typedef void result_type;

	explicit set_pixel(
		color const &src);
	
	template<
		typename Dest
	>
	void operator()(
		Dest const &) const;
private:
	color const src;
};

}
}
}

sge::gui::utility::set_pixel::set_pixel(
	color const &src)
:
	src(src)
{}

template<
	typename Dest
>
void sge::gui::utility::set_pixel::operator()(
	Dest const &d) const
{
	*d.at(0, 0)
		= renderer::any_color_convert<
			typename Dest::locator::value_type
		>(
			src);
		
}

#endif
