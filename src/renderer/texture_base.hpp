/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TEXTURE_BASE_HPP_INCLUDED
#define SGE_TEXTURE_BASE_HPP_INCLUDED

#include <cstddef>
#include "../shared_ptr.hpp"
#include "../math/rect.hpp"
#include "color.hpp"
#include "types.hpp"

namespace sge
{

template<typename BitDepth>
class basic_texture_base {
public:
	typedef std::size_t              size_type;
	typedef std::ptrdiff_t           difference_type;
	typedef typename BitDepth::color value_type;
	typedef value_type*              pointer;
	typedef const value_type*        const_pointer;
	virtual ~basic_texture_base() {}
	virtual size_type size() const = 0;
	virtual resource_flag_t flags() const = 0;
	virtual void filter(const filter_args&) = 0;
};

typedef basic_texture_base<bit_depth32> texture_base;
typedef shared_ptr<texture_base> texture_base_ptr;
typedef math::basic_rect<texture_base::size_type> lock_rect;

}

#endif
