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
#include <sge/math/rect/contains_point.hpp>
#include <sge/math/rect/structure_cast.hpp>
#include <sge/math/rect/output.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/text.hpp>
#include <sge/renderer/fill_pixels.hpp>
#include <sge/renderer/subimage_view.hpp>
#include <sge/lexical_cast.hpp>

void sge::gui::canvas::object::draw_pixel(
	point const &p,
	color const c)
{
	SGE_ASSERT_MESSAGE(
		contains_point(area(),p),
		SGE_TEXT("tried to draw pixel ")+
		lexical_cast<string>(p)+
		SGE_TEXT(" which is not inside rect ")+
		lexical_cast<string>(area()));
	
	renderer::fill_pixels(
		renderer::subimage_view(
			view_,
			math::rect::structure_cast<
				renderer::lock_rect
			>(
				rect(
					p,
					dim(1,1)
				)
			)
		),
		c
	);
}
