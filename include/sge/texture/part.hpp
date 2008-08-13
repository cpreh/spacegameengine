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


#ifndef SGE_TEXTURE_PART_HPP_INCLUDED
#define SGE_TEXTURE_PART_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "../export.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/image_view.hpp"
#include "../renderer/types.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace texture
{

class fragmented;

class part : boost::noncopyable {
public:
	SGE_SYMBOL virtual ~part();

	SGE_SYMBOL const math::rect area_texc(
		space_unit repeat = 1) const;

	SGE_SYMBOL const renderer::tex_pos translate(
		const renderer::tex_pos &local_coords,
		space_unit repeat = 1) const;

	virtual void data(
		renderer::const_image_view const &src) = 0;

	virtual renderer::lock_rect const &area() const = 0;

	virtual renderer::texture_ptr const my_texture() = 0;
	
	virtual renderer::const_texture_ptr const my_texture() const = 0;

	virtual bool repeatable() const = 0;
};

typedef shared_ptr<part>       part_ptr;
typedef shared_ptr<const part> const_part_ptr;

}
}

#endif
