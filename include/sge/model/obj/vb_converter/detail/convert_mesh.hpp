#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_MESH_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_MESH_HPP_INCLUDED

#include <sge/model/obj/vb_converter/detail/convert_face.hpp>
#include <sge/model/obj/mesh.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/instance_fwd.hpp>
#include <sge/model/obj/face.hpp>

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
