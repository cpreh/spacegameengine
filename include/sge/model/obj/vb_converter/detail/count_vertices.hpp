#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_COUNT_VERTICES_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_COUNT_VERTICES_HPP_INCLUDED

#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/mesh_sequence.hpp>
#include <sge/model/obj/mesh.hpp>
#include <sge/model/obj/face_sequence.hpp>
#include <sge/model/obj/face.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/utility/enable_if.hpp>

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
template<typename Result>
typename
boost::enable_if
<
	boost::is_integral<Result>,
	Result
>::type
count_vertices(
	sge::model::obj::instance const &_model)
{
	Result result =
		static_cast<Result>(
			0);

	for(
		obj::mesh_sequence::const_iterator mesh_it =
			_model.meshes().begin();
		mesh_it != _model.meshes().end();
		++mesh_it)
		for(
			obj::face_sequence::const_iterator face_it =
				mesh_it->faces_.begin();
			face_it != mesh_it->faces_.end();
			++face_it)
			result =
				static_cast<Result>(
					result +
					face_it->points_.size());
	return result;
}
}
}
}
}
}

#endif
