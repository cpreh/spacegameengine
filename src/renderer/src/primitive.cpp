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


#include "../primitive.hpp"
#include "../../exception.hpp"

std::size_t sge::indices_per_primitive(const indexed_primitive_type::type prim)
{
	switch(prim) {
	case indexed_primitive_type::triangle:
		return 3;
	case indexed_primitive_type::line:
		return 2;
	default:
		throw exception(SGE_TEXT("indices_per_primitive: Invalid indexed_primitive_format!"));
	}
}

std::size_t sge::primitive_count(const std::size_t vertex_count, const nonindexed_primitive_type::type prim)
{
	switch(prim) {
	case nonindexed_primitive_type::point:
		return vertex_count;
	case nonindexed_primitive_type::line_strip:
		if(vertex_count <= 1)
			throw exception(SGE_TEXT("primitive_count(): line_strip needs at least two vertices!"));
		return vertex_count - 1;
	case nonindexed_primitive_type::triangle_strip:
	case nonindexed_primitive_type::triangle_fan:
		if(vertex_count <= 2)
			throw exception(SGE_TEXT("primitive_count(): triangles need at least three vertices!"));
		return vertex_count - 2;
	default:
		throw exception(SGE_TEXT("Invalid nonindexed_primitive_type!"));
	}
}
