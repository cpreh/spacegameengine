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


#include <sge/renderer/cube_texture.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/power.hpp>
#include <sge/variant/object_impl.hpp>

sge::renderer::image_view const
sge::renderer::cube_texture::lock(
	cube_side::type const side,
	lock_flag_type const flags)
{
	return lock(
		side,
		rect(),
		flags
	);
}

sge::renderer::const_image_view const
sge::renderer::cube_texture::lock(
	cube_side::type const side) const
{
	return lock(
		side,
		rect()
	);
}

sge::renderer::cube_texture::size_type
sge::renderer::cube_texture::content() const
{
	return math::quad(
		border_size()
	);
}

sge::renderer::cube_texture::rect_type const
sge::renderer::cube_texture::rect() const
{
	return rect_type(
		rect_type::point_type::null(),
		rect_type::dim_type(
			border_size(),
			border_size()
		)
	);
}
