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


#ifndef SGE_PRIMITIVE_HPP_INCLUDED
#define SGE_PRIMITIVE_HPP_INCLUDED

#include <cstddef>
#include "../export.hpp"

namespace sge
{

namespace indexed_primitive_type
{
	enum type {
		line,
		triangle
	};
}

namespace nonindexed_primitive_type
{
	enum type {
		point,
		line_strip,
		line_loop,
		triangle_strip,
		triangle_fan
	};
}

SGE_SYMBOL std::size_t indices_per_primitive(indexed_primitive_type::type);
SGE_SYMBOL std::size_t primitive_count(std::size_t vertex_count, nonindexed_primitive_type::type prim);

}

#endif
