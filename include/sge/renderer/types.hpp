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


#ifndef SGE_RENDERER_TYPES_HPP_INCLUDED
#define SGE_RENDERER_TYPES_HPP_INCLUDED

#include "../export.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "../math/rect.hpp"
#include "color.hpp"
#include <cstddef>

namespace sge
{
namespace renderer
{

namespace bit_depth
{
	enum type {
		depth16 = 16,
		depth32 = 32
	};
}

SGE_SYMBOL unsigned bit_depth_bit_count(bit_depth::type);

typedef int                              pixel_unit;
typedef unsigned                         screen_unit;
typedef math::basic_vector<pixel_unit,2> pixel_pos_t;
typedef math::basic_dim<screen_unit,2>   screen_size_t;

typedef unsigned multi_sample_type;

namespace resource_flags
{
	enum type {
		none,
		dynamic     = 1,
		write_only  = 1 << 1,
		default_    = write_only
	};
}
typedef unsigned resource_flag_t;

namespace lock_flags
{
	enum type {
		readonly,
		writeonly,
		readwrite
	};
}

typedef lock_flags::type lock_flag_t;

SGE_SYMBOL bool lock_flag_write(lock_flag_t mode);
SGE_SYMBOL bool lock_flag_read(lock_flag_t mode);

typedef math::vector2  tex_pos;
typedef math::rect     tex_rect;
typedef math::vector2  pos2;
typedef math::vector3  pos3;

typedef std::size_t stage_type;

}
}

#endif
