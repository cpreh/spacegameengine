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


#ifndef SGE_TEXTURE_CELL_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_CELL_FRAGMENTED_HPP_INCLUDED

#include "../export.hpp"
#include "../raw_vector.hpp"
#include "../field.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/texture_filter.hpp"
#include "fragmented.hpp"
#include "part.hpp"

namespace sge
{
namespace texture
{

class cell_fragmented : public fragmented {
public:
	SGE_SYMBOL cell_fragmented(
		renderer::device_ptr rend,
		const renderer::filter_args& filter,
		const renderer::texture::dim_type& cell_size);
	SGE_SYMBOL const part_ptr consume_fragment(
		const renderer::texture::dim_type&);
	SGE_SYMBOL void return_fragment(
		const part&);
	SGE_SYMBOL const renderer::texture_ptr get_texture() const;
	SGE_SYMBOL bool repeatable() const;
private:
	typedef field<bool, raw_vector> field_type;
	const renderer::device_ptr      rend;
	const renderer::filter_args     my_filter;
	renderer::texture::dim_type     cell_size;
	field_type                      cells;
	const renderer::texture_ptr     tex;
};

}
}

#endif
