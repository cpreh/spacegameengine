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


#ifndef SGE_RENDERER_CUBE_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_CUBE_TEXTURE_HPP_INCLUDED

#include "image_view.hpp"
#include "texture_base.hpp"
#include "lock_rect.hpp"
#include "../export.hpp"
#include <boost/array.hpp>

namespace sge
{
namespace renderer
{

namespace cube_side
{
	enum type {
		front,
		back,
		left,
		right,
		top,
		bottom,
		num_elements
	};
}

class SGE_CLASS_SYMBOL cube_texture : public texture_base {
public:
	typedef boost::array<
		image_view,
		cube_side::num_elements
	> image_view_6;
	typedef lock_rect rect_type;

	SGE_SYMBOL image_view const lock(
		cube_side::type side,
		lock_flag_type);

	SGE_SYMBOL const_image_view const lock(
		cube_side::type side) const;

	virtual image_view const lock(
		cube_side::type side,
		lock_rect const &,
		lock_flag_type) = 0;
	
	virtual const_image_view const lock(
		cube_side::type side,
		lock_rect const &) const = 0;

	virtual void unlock() const = 0;

	SGE_SYMBOL size_type content() const;
	SGE_SYMBOL rect_type const rect() const;
	virtual size_type border_size() const = 0;
};

}
}

#endif
