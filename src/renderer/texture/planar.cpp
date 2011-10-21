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


#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <fcppt/math/box/basic_impl.hpp>


sge::renderer::texture::planar::planar()
{
}

sge::renderer::texture::planar::~planar()
{
}

sge::renderer::texture::planar::view const
sge::renderer::texture::planar::lock(
	lock_mode::type const _flags
)
{
	return
		this->lock(
			this->area(),
			_flags
		);
}

sge::renderer::texture::planar::const_view const
sge::renderer::texture::planar::lock() const
{
	return
		this->lock(
			this->area()
		);
}

sge::renderer::texture::planar::rect const
sge::renderer::texture::planar::area() const
{
	return
		planar::rect(
			planar::rect::vector::null(),
			this->size()
		);
}

sge::renderer::texture::planar::size_type
sge::renderer::texture::planar::content() const
{
	return
		this->size().content();
}
