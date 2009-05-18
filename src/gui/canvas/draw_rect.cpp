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
#include <sge/assert.hpp>
#include <sge/math/rect/contains.hpp>
#include <sge/math/rect/structure_cast.hpp>
#include <sge/math/rect/output.hpp>
#include <sge/image/algorithm/fill.hpp>
#include <sge/image/view/sub.hpp>
#include <sge/lexical_cast.hpp>

void sge::gui::canvas::object::draw_rect(
	rect const &r,
	color const c,
	rect_type::type const t)
{
	SGE_ASSERT_MESSAGE(
		contains(area(),r),
		SGE_TEXT("tried to draw rectangle ")+
			lexical_cast<string>(r)+
			SGE_TEXT(" which is not completely inside ")+
			lexical_cast<string>(area()));

	switch (t)
	{
		case rect_type::solid:
			sge::image::algorithm::fill(
				sge::image::view::sub(
					view_,
					math::rect::structure_cast<
						sge::image::rect
					>(r)
				),
				c
			);
		break;
		case rect_type::outline:
		{
			point_container ps;
			ps.push_back(point(r.left(),r.top()));
			ps.push_back(point(r.left(),r.bottom()));
			ps.push_back(point(r.right(),r.bottom()));
			ps.push_back(point(r.right(),r.top()));
			draw_line_strip(
				ps,
				c,
				line_type::solid,
				strip_type::closed);
		}
		break;
	}
}
