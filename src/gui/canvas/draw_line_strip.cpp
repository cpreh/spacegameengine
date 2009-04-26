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
#include <sge/gui/canvas/object.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/assert.hpp>

void sge::gui::canvas::object::draw_line_strip(
	point_container const &points,
	color const c,
	line_type::type const lt,
	strip_type::type const st)
{
	SGE_ASSERT(points.size() > 1);

	for (point_container::size_type i = 0;
		i < static_cast<point_container::size_type>(points.size()-1);
		++i)
		draw_line(points[i],points[i+1],c,lt);

	switch (st)
	{
		case strip_type::open:
		break;
		case strip_type::closed:
			draw_line(points[points.size()-1],points[0],c,lt);
		break;
	}
}
