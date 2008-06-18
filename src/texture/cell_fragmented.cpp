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
#include <sge/texture/cell_fragmented.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/exception.hpp>
#include <cassert>

sge::texture::cell_fragmented::cell_fragmented(
	const renderer::device_ptr rend,
	const renderer::filter_args& filter,
	const renderer::texture::dim_type& cell_size)
: rend(rend),
  my_filter(filter),
  cell_size(cell_size),
  cells(atlased_texture_dim(rend) / cell_size, false),
  tex(atlased_texture(rend, my_filter))
{}

const sge::texture::part_ptr
sge::texture::cell_fragmented::consume_fragment(
	const renderer::texture::dim_type& dim)
{
	if(dim != cell_size)
		throw exception(SGE_TEXT("Invalid request for consume_fragments in texture::cell_fragmented!"));
	// TODO maybe optimize this with a stack?
	const field_type::iterator it = std::find(cells.begin(), cells.end(), false);
	if(it == cells.end())
		return part_ptr();
	*it = true;
	
	const field_type::vector_type pos = cells.position(it);
	return part_ptr(
		new part_fragmented(
			renderer::lock_rect(
				pos + cell_size, cell_size),
			*this,
			true,
			true));
}

void sge::texture::cell_fragmented::return_fragment(
	const part& t)
{
	const field_type::vector_type pos = t.area().pos() * cell_size;
	assert(cells.pos(pos));
	cells.pos(pos) = false;
}

const sge::renderer::texture_ptr
sge::texture::cell_fragmented::get_texture() const
{
	return tex;
}

bool sge::texture::cell_fragmented::repeatable() const
{
	return false;
}
