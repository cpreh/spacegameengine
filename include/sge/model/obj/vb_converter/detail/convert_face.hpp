#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_FACE_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_FACE_HPP_INCLUDED

#include <sge/model/obj/vb_converter/detail/convert_face_point.hpp>
#include <sge/model/obj/instance_fwd.hpp>
#include <sge/model/obj/face.hpp>
#include <sge/model/obj/face_point_sequence.hpp>
#include <fcppt/assert.hpp>

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
	FCPPT_ASSERT(
		_face.points_.size() == 3);

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
