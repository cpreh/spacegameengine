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


#include <sge/texture/part.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/renderer/transform.hpp>
#include <sge/math/compare.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/iostream.hpp>
#include <ostream>

sge::texture::part::~part()
{}

const sge::math::rect
sge::texture::part::area_texc(
	const space_unit repeat) const
{
	if(!math::compare(repeat, static_cast<space_unit>(1)) && !repeatable())
		sge::cerr << SGE_TEXT("Warning: texture not repeatable but repetition is ") << repeat << SGE_TEXT("!\n");

	const renderer::const_texture_ptr tex = my_texture();
	return tex
		? renderer::tex_size_to_space_rect(
			area(),
			tex->dim(),
			repeat)
		: math::rect();
}

const sge::renderer::tex_pos
sge::texture::part::translate(
	const renderer::tex_pos &local_coords,
	const space_unit repeat) const
{
	const sge::math::rect texc = area_texc(repeat);
	return sge::renderer::tex_pos(
		(1 - local_coords.x()) * texc.left() + local_coords.y() * texc.right(),
		(1 - local_coords.x()) * texc.top() + local_coords.y() * texc.bottom()
	);
}

void sge::texture::part::lock(
	renderer::lock_flags::type const lflags)
{
	my_texture()->lock(
		area(),
		lflags);
}

void sge::texture::part::unlock()
{
	my_texture()->unlock();
}
