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


#ifndef SGE_GRID_FRAGMENTED_TEXTURE_HPP_INCLUDED
#define SGE_GRID_FRAGMENTED_TEXTURE_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include "fragmented_texture.hpp"

namespace sge
{

class grid_fragmented_texture : public fragmented_texture, boost::noncopyable {
public:
	grid_fragmented_texture(renderer_ptr rend, const texture::dim_type&, const filter_args& filter);
	const virtual_texture_ptr consume_fragments(const texture::dim_type&);
	void return_fragments(const virtual_texture&);
	const texture_ptr get_texture() const;
	bool repeatable() const;
private:
	const renderer_ptr rend;
	const filter_args  my_filter;
	texture::size_type part_width, part_height;
	texture_ptr        tex;
	texture::size_type tex_x_size, tex_y_size;
	unsigned parts_per_row, parts_total, parts_free;
	boost::scoped_array<bool> reserved;
};

}

#endif
