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


#include <cassert>
#include "../../exception.hpp"
#include "../../raw_vector_impl.hpp"
#include "../../math/vec_dim.hpp"
#include "../../math/rect_impl.hpp"
#include "../atlasing.hpp"
#include "../cell_fragmented_texture.hpp"

sge::cell_fragmented_texture::cell_fragmented_texture(const renderer_ptr rend,
                                                      const filter_args& filter,
                                                      const texture::dim_type& cell_size)
: rend(rend),
  my_filter(filter),
  cell_size(cell_size),
  cells(atlased_texture_dim(rend) / cell_size, false),
  tex(atlased_texture(rend, my_filter))
{}

const sge::virtual_texture_ptr sge::cell_fragmented_texture::consume_fragments(const texture::dim_type& dim)
{
	if(dim != cell_size)
		throw exception("Invalid request for consume_fragments in cell_fragmented_texture!");
	// TODO maybe optimize this with a stack?
	const field_type::iterator it = std::find(cells.begin(), cells.end(), false);
	if(it == cells.end())
		return virtual_texture_ptr();
	*it = true;
	
	const field_type::coord_vector_type pos = cells.position(it);
	return virtual_texture_ptr(new virtual_texture(lock_rect(pos + cell_size, cell_size), *this));
}

void sge::cell_fragmented_texture::return_fragments(const virtual_texture& t)
{
	const field_type::coord_vector_type pos = t.area().pos() * cell_size;
	assert(cells.pos(pos));
	cells.pos(pos) = false;
}

const sge::texture_ptr sge::cell_fragmented_texture::get_texture() const
{
	return tex;
}

bool sge::cell_fragmented_texture::repeatable() const
{
	return false;
}
