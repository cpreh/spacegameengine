#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_TEXCOORD_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_TEXCOORD_HPP_INCLUDED

#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/face_point.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/void.hpp>

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
template<typename TexcoordIndex,typename VertexFormatPart,typename Vertex>
typename
boost::enable_if
<
	boost::is_same<TexcoordIndex,boost::mpl::void_>,
	void
>::type
convert_texcoord(
	obj::instance const &,
	obj::face_point const &,
	Vertex const &)
{
}

template<typename TexcoordIndex,typename VertexFormatPart,typename Vertex>
typename
boost::disable_if
<
	boost::is_same<TexcoordIndex,boost::mpl::void_>,
	void
>::type
convert_texcoord(
	obj::instance const &_model,
	obj::face_point const &_face_point,
	Vertex const &_vertex)
{
	typedef typename
	boost::mpl::at
	<
		typename VertexFormatPart::elements,
		TexcoordIndex
	>::type
	texcoord_type;

	obj::texcoord const origin =
		_model.texcoords()[*_face_point.texcoord_index_];

	typename texcoord_type::packed_type texcoord_vector;
	texcoord_vector[0] = origin.t1_;
	texcoord_vector[1] = origin.t2_;

	// Instead of a runtime if, this could be a compile time if, of
	// course. But I was lazy and didn't think it mattered much (what
	// with optimizing and all).
	if(texcoord_vector.size() == 3)
		texcoord_vector[2] = *origin.t3_;

	_vertex->template set<texcoord_type>(
		texcoord_vector);
}
}
}
}
}
}

#endif
