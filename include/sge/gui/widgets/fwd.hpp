/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_WIDGETS_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGETS_FWD_HPP_INCLUDED

#include <boost/mpl/vector.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class base;
class edit;
class label;
class graphics;
class backdrop;
class scroll;

namespace buttons
{
class text;
class image;
}

#define SGE_GUI_WIDGETS_FWD_APPLY(begin_func,func,end_func)\
	begin_func(edit)\
	func(label)\
	func(graphics)\
	func(backdrop)\
	func(buttons::text)\
	end_func(buttons::image)

#define SGE_GUI_WIDGETS_FWD_COMMA_WIDGET(w) w,
#define SGE_GUI_WIDGETS_FWD_NO_COMMA_WIDGET(w) w

typedef boost::mpl::vector<
	SGE_GUI_WIDGETS_FWD_APPLY(SGE_GUI_WIDGETS_FWD_COMMA_WIDGET,SGE_GUI_WIDGETS_FWD_COMMA_WIDGET,SGE_GUI_WIDGETS_FWD_NO_COMMA_WIDGET)
> types;
}
}
}

#endif
