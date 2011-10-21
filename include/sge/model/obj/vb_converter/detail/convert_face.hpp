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


#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_FACE_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_FACE_HPP_INCLUDED

#include <sge/model/obj/face.hpp>
#include <sge/model/obj/face_point_sequence.hpp>
#include <sge/model/obj/instance_fwd.hpp>
#include <sge/model/obj/vb_converter/detail/convert_face_point.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre_message.hpp>


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
template
<
	typename VertexFormatPart,
	typename PositionMap,
	typename VertexIterator
>
void
convert_face(
	obj::instance const &_model,
	VertexIterator &_current_vertex,
	obj::face const &_face)
{
	FCPPT_ASSERT_PRE_MESSAGE(
		_face.points_.size() == 3,
		FCPPT_TEXT("Only triangles are allowed for conversion"));

	for(
		obj::face_point_sequence::const_iterator vertex_it =
			_face.points_.begin();
		vertex_it != _face.points_.end();
		++vertex_it)
		detail::convert_face_point<VertexFormatPart,PositionMap>(
			_model,
			*vertex_it,
			_current_vertex);
}
}
}
}
}
}

#endif
