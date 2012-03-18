/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>


sge::renderer::texture::volume::volume()
{
}

sge::renderer::texture::volume::~volume()
{
}

sge::renderer::texture::volume::view const
sge::renderer::texture::volume::lock(
	renderer::lock_mode::type const _flags
)
{
	return
		this->lock(
			this->area(),
			_flags
		);
}

sge::renderer::texture::volume::const_view const
sge::renderer::texture::volume::lock() const
{
	return
		this->lock(
			this->area()
		);
}

sge::renderer::texture::volume::box const
sge::renderer::texture::volume::area() const
{
	return
		volume::box(
			volume::box::vector::null(),
			this->size()
		);
}

sge::renderer::texture::volume::size_type
sge::renderer::texture::volume::content() const
{
	return
		this->size().content();
}
