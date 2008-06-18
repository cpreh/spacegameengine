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


#include <sge/texture/atlasing.hpp>
#include <sge/texture/cell_fragmented_texture.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/exception.hpp>
#include <cassert>

sge::cell_fragmented_texture::cell_fragmented_texture(
	const renderer::device_ptr rend,
	const renderer::filter_args& filter,
	const renderer::texture::dim_type& cell_size)
: rend(rend),
  my_filter(filter),
  cell_size(cell_size),
  cells(atlased_texture_dim(rend) / cell_size, false),
  tex(atlased_texture(rend, my_filter))
{}

const sge::virtual_texture_ptr
sge::cell_fragmented_texture::consume_fragments(
	const renderer::texture::dim_type& dim)
{
	if(dim != cell_size)
		throw exception(SGE_TEXT("Invalid request for consume_fragments in cell_fragmented_texture!"));
	// TODO maybe optimize this with a stack?
	const field_type::iterator it = std::find(cells.begin(), cells.end(), false);
	if(it == cells.end())
		return virtual_texture_ptr();
	*it = true;
	
	const field_type::vector_type pos = cells.position(it);
	return virtual_texture_ptr(
		new virtual_texture(
			renderer::lock_rect(
				pos + cell_size, cell_size),
			*this,
			true,
			true));
}

void sge::cell_fragmented_texture::return_fragments(const virtual_texture& t)
{
	const field_type::vector_type pos = t.area().pos() * cell_size;
	assert(cells.pos(pos));
	cells.pos(pos) = false;
}

const sge::renderer::texture_ptr
sge::cell_fragmented_texture::get_texture() const
{
	return tex;
}

bool sge::cell_fragmented_texture::repeatable() const
{
	return false;
}
