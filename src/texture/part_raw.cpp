/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/part_raw.hpp>
#include <sge/renderer/texture_util.hpp>
#include <sge/math/rect_impl.hpp>

sge::texture::part_raw::part_raw(
	renderer::lock_rect const &area_,
	const renderer::texture_ptr tex)
: area_(area_),
  tex(tex)
{}

void sge::texture::part_raw::data(
	renderer::const_image_view const &src)
{
	renderer::sub_data(tex, src, area().pos());
}

sge::renderer::lock_rect const &
sge::texture::part_raw::area() const
{
	return area_;
}

sge::renderer::texture_ptr const
sge::texture::part_raw::my_texture()
{
	return tex;
}

sge::renderer::const_texture_ptr const
sge::texture::part_raw::my_texture() const
{
	return tex;
}

bool sge::texture::part_raw::repeatable() const
{
	return area().dim() == tex->dim();
}
