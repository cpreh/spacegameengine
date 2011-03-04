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


#include <sge/renderer/texture/cube.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/quad.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::renderer::texture::cube::cube()
{
}

sge::image2d::view::object const
sge::renderer::texture::cube::lock(
	cube_side::type const _side,
	lock_mode::type const _flags
)
{
	return
		this->lock(
			_side,
			this->rect(),
			_flags
		);
}

sge::image2d::view::const_object const
sge::renderer::texture::cube::lock(
	cube_side::type const _side
) const
{
	return
		this->lock(
			_side,
			this->rect()
		);
}

sge::renderer::texture::cube::size_type
sge::renderer::texture::cube::content() const
{
	return
		fcppt::math::quad(
			this->border_size()
		);
}

sge::renderer::texture::cube::rect_type const
sge::renderer::texture::cube::rect() const
{
	return
		rect_type(
			rect_type::vector::null(),
			rect_type::dim(
				this->border_size(),
				this->border_size()
			)
		);
}

sge::renderer::texture::cube::rect_type const
sge::renderer::texture::cube::area() const
{
	return this->rect();
}

sge::renderer::texture::cube::~cube()
{
}
