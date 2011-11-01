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


#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/convert/cube_side.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <fcppt/assert/pre.hpp>


sge::opengl::texture::type const
sge::opengl::texture::convert::cube_side(
	texture::cube_side_array const &_cube_sides,
	renderer::texture::cube_side::type const _side
)
{
	cube_side_array::size_type const pos(
		static_cast<
			cube_side_array::size_type
		>(
			_side
		)
	);

	FCPPT_ASSERT_PRE(
		pos < _cube_sides.size()
	);

	return
		_cube_sides[
			pos
		];
}
