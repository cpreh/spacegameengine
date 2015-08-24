/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/vector/null.hpp>


sge::renderer::texture::planar::planar()
{
}

sge::renderer::texture::planar::~planar()
{
}

sge::renderer::texture::planar::dim const
sge::renderer::texture::planar::size() const
{
	return
		this->level(
			sge::renderer::texture::mipmap::level(
				0u
			)
		).size();
}

sge::renderer::texture::planar::rect const
sge::renderer::texture::planar::area() const
{
	return
		sge::renderer::texture::planar::rect(
			fcppt::math::vector::null<
				sge::renderer::texture::planar::rect::vector
			>(),
			this->size()
		);
}

sge::renderer::texture::planar::size_type
sge::renderer::texture::planar::content() const
{
	return
		fcppt::math::dim::contents(
			this->size()
		);
}
