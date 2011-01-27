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


#include "../get_scissor_area.hpp"
#include "../get_ints.hpp"
#include <fcppt/container/array.hpp>
#include <fcppt/math/box/basic_impl.hpp>

sge::renderer::scissor_area const
sge::opengl::get_scissor_area()
{
	fcppt::container::array<
		GLint,
		4
	> temp;

	opengl::get_ints(
		GL_SCISSOR_BOX,
		temp.data()
	);

	return
		sge::renderer::scissor_area(
			sge::renderer::pixel_rect(
				sge::renderer::pixel_rect::vector(
					temp[0],
					temp[1]
				),
				sge::renderer::pixel_rect::dim(
					temp[2],
					temp[3]
				)
			)
		);
}
