/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/export.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/image/color/format.hpp>

namespace sge
{
namespace renderer
{
namespace filter
{
class texture;
}
}

namespace texture
{

class rect_fragmented : public fragmented {
public:
	SGE_SYMBOL rect_fragmented(
		renderer::device_ptr rend,
		image::color::format::type,
		renderer::filter::texture const &filter);
private:
	SGE_SYMBOL part_ptr const
	consume_fragment(
		renderer::dim_type const &);
	SGE_SYMBOL void on_return_fragment(
		part const &);
	SGE_SYMBOL renderer::texture_ptr const
	texture() const;
	SGE_SYMBOL bool repeatable() const;

	SGE_SYMBOL free_type
	free_value() const;

	SGE_SYMBOL bool
	empty() const;

	renderer::device_ptr  const  rend;
	renderer::size_type          cur_x,
	                             cur_y,
	                             cur_height;
	renderer::texture_ptr const  tex;
	renderer::size_type          texture_count;
};

}
}

#endif
