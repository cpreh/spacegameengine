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


#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_MESH_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_MESH_HPP_INCLUDED

#include <sge/model/obj/face.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/instance_fwd.hpp>
#include <sge/model/obj/mesh.hpp>
#include <sge/model/obj/vb_converter/detail/convert_face.hpp>


namespace sge
{
namespace model
{
namespace obj
{
namespace vb_converter
{
namespace detail
{
template<typename VertexFormatPart,typename PositionMap,typename VertexIterator>
void
convert_mesh(
	obj::instance const &_model,
	VertexIterator &_current_vertex,
	obj::mesh const &_mesh)
{
	for(
		obj::face_sequence::const_iterator face_it =
			_mesh.faces_.begin();
		face_it != _mesh.faces_.end();
		++face_it)
	{
		detail::convert_face<VertexFormatPart,PositionMap>(
			_model,
			_current_vertex,
			*face_it);
	}
}
}
}
}
}
}

#endif
