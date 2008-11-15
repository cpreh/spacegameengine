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


/*#ifndef SGE_GRID_FRAGMENTED_TEXTURE_HPP_INCLUDED
#define SGE_GRID_FRAGMENTED_TEXTURE_HPP_INCLUDED

#include "fragmented_texture.hpp"
#include "../export.hpp"
#include "../renderer/texture_filter.hpp"
#include "../renderer/device.hpp"
#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>

namespace sge
{

class grid_fragmented_texture : public fragmented_texture, boost::noncopyable {
public:
	SGE_SYMBOL grid_fragmented_texture(
		renderer::device_ptr rend,
		const renderer::texture::dim_type&,
		const renderer::texture_filter& filter);
	SGE_SYMBOL const virtual_texture_ptr consume_fragment(
		const renderer::texture::dim_type&);
	SGE_SYMBOL void return_fragment(
		const virtual_texture&);
	SGE_SYMBOL const renderer::texture_ptr get_texture() const;
	SGE_SYMBOL bool repeatable() const;
private:
	const renderer::device_ptr   rend;
	const renderer::texture_filter  my_filter;
	renderer::texture::size_type part_width,
	                             part_height;
	renderer::texture_ptr        tex;
	renderer::texture::size_type tex_x_size,
	                             tex_y_size;
	unsigned                     parts_per_row,
	                             parts_total,
	                             parts_free;
	boost::scoped_array<bool>    reserved;
};

}

#endif*/
