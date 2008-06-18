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


#ifndef SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED

#include "fragmented.hpp"
#include "../export.hpp"
#include "../renderer/device.hpp"
#include "../renderer/texture_filter.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace texture
{

// FIXME
// this is just a temporary hack
class rect_fragmented : public fragmented, boost::noncopyable {
public:
	SGE_SYMBOL rect_fragmented(
		renderer::device_ptr rend,
		const renderer::filter_args& filter);
	SGE_SYMBOL const part_ptr consume_fragment(
		const renderer::texture::dim_type&);
	SGE_SYMBOL void return_fragment(
		const part&);
	SGE_SYMBOL const renderer::texture_ptr get_texture() const;
	SGE_SYMBOL bool repeatable() const;
private:
	const renderer::device_ptr   rend;
	const renderer::filter_args  my_filter;
	renderer::texture::size_type cur_x,
	                             cur_y,
	                             cur_height;
	const renderer::texture_ptr  tex;
};

}
}

#endif
