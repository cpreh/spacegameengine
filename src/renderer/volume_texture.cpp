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


#include <sge/renderer/volume_texture.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>

sge::renderer::volume_texture::volume_texture()
{
}

sge::renderer::volume_texture::~volume_texture()
{
}

sge::renderer::volume_texture::view_type const
sge::renderer::volume_texture::lock(
	lock_mode::type const _flags
)
{
	return
		lock(
			box(),
			_flags
		);
}

sge::renderer::volume_texture::const_view_type const
sge::renderer::volume_texture::lock() const
{
	return
		lock(
			box()
		);
}

sge::renderer::volume_texture::box_type const
sge::renderer::volume_texture::box() const
{
	return
		box_type(
			box_type::vector::null(),
			dim()
		);
}

sge::renderer::volume_texture::box_type const
sge::renderer::volume_texture::area() const
{
	return box();
}

sge::renderer::volume_texture::size_type
sge::renderer::volume_texture::content() const
{
	return dim().content();
}
