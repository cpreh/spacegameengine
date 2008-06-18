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


#include <sge/texture/static.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>

sge::texture::static_::static_(
	const renderer::texture_ptr tex)
: tex(tex),
  claimed(false)
{}

const sge::texture::part_ptr
sge::texture::static_::consume_fragment(
	const renderer::texture::dim_type& dim)
{
	if(claimed)
		return part_ptr();

	if(dim.w() > tex->dim().w() || dim.h() > tex->dim().h())
		throw exception(SGE_TEXT("texture::static_::consume_fragments(): size out of range."));
	claimed = true;
	return part_ptr(
		new part_fragmented(
			renderer::lock_rect(
				renderer::lock_rect::point_type(0, 0),
				dim),
			*this,
			false,
			false));
}

void sge::texture::static_::return_fragment(
	const part&)
{
	claimed = false;
}

const sge::renderer::texture_ptr
sge::texture::static_::get_texture() const
{
	return tex;
}

bool sge::texture::static_::repeatable() const
{
	return true;
}
