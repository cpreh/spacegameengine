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


#include <sge/renderer/dim3.hpp>
#include <sge/renderer/lock_box.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/color_buffer/volume.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


sge::renderer::texture::volume::volume()
{
}

sge::renderer::texture::volume::~volume()
{
}

sge::renderer::texture::volume::dim const
sge::renderer::texture::volume::size() const
{
	return
		this->level(
			sge::renderer::texture::mipmap::level(
				0u
			)
		).size();
}

sge::renderer::texture::volume::rect const
sge::renderer::texture::volume::area() const
{
	return
		sge::renderer::texture::volume::rect(
			sge::renderer::texture::volume::rect::vector::null(),
			this->size()
		);
}

sge::renderer::texture::volume::size_type
sge::renderer::texture::volume::content() const
{
	return
		this->size().content();
}
