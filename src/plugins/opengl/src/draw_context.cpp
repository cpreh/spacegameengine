/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../draw_context.hpp"
#include "../context/make_id.hpp"
#include "../glew/is_supported.hpp"

sge::opengl::draw_context::draw_context()
:
	draw_range_elements_supported_(
		glew::is_supported(
			"GL_VERSION_1_2"
		)
	),
	draw_range_elements_ext_supported_(
		glDrawRangeElementsEXT
	),
	draw_range_elements_(
		draw_range_elements_supported_
		?
			glDrawRangeElements
		:
			draw_range_elements_ext_supported_
			?
				glDrawRangeElementsEXT
			:
				0
	)
{
}

sge::opengl::draw_context::~draw_context()
{
}

bool
sge::opengl::draw_context::draw_range_elements_supported() const
{
	return
		draw_range_elements_supported_
		|| draw_range_elements_ext_supported_;
}

sge::opengl::draw_context::gl_draw_range_elements
sge::opengl::draw_context::draw_range_elements() const
{
	return draw_range_elements_;
}

sge::opengl::context::id const
sge::opengl::draw_context::static_id(
	sge::opengl::context::make_id()
);
