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


#ifndef SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED
#define SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED

#include <sge/gui/image_view.hpp>
#include <sge/gui/rect.hpp>
#include <sge/gui/export.hpp>
#include <sge/math/box/basic_impl.hpp>
#include <sge/variant/object_impl.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class invalid_area
{
public:
	SGE_GUI_SYMBOL invalid_area(
		image_view const &,
		rect const &);
	SGE_GUI_SYMBOL image_view const &texture() const;
	SGE_GUI_SYMBOL rect const area() const;
private:
	// image view
	image_view texture_;
	// the (absolute) area which is invalid
	rect const area_;
};
}
}
}

#endif
