/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MODEL_OBJ_FACE_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_HPP_INCLUDED

#include <sge/model/obj/vertex_sequence.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace model
{
namespace obj
{
class face
{
public:
	typedef
	std::vector<vertex_sequence::size_type>
	vertex_indices;

	typedef
	std::vector<texcoord_sequence::size_type>
	texcoord_indices;

	typedef
	std::vector<normal_sequence::size_type>
	normal_indices;

	typedef
	fcppt::optional<texcoord_indices>
	optional_texcoord_indices;

	typedef
	fcppt::optional<normal_indices>
	optional_normal_indices;

	vertex_indices const &
	vertices() const;

	optional_texcoord_indices const &
	texcoords() const;

	optional_normal_indices const &
	normals() const;
private:
	vertex_indices vertices_;
	optional_texcoord_indices texcoords_;
	optional_normal_indices normals_;
};
}
}
}

#endif
