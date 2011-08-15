#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_NORMAL_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_NORMAL_HPP_INCLUDED

#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/face_point.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/assert/error.hpp>
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
template<typename NormalIndex,typename VertexFormatPart,typename Vertex>
typename
boost::enable_if
<
	boost::is_same<NormalIndex,boost::mpl::void_>,
	void
>::type
convert_normal(
	obj::instance const &,
	obj::face_point const &,
	Vertex const &)
{
}

template<typename NormalIndex,typename VertexFormatPart,typename Vertex>
typename
boost::disable_if
<
	boost::is_same<NormalIndex,boost::mpl::void_>,
	void
>::type
convert_normal(
	obj::instance const &_model,
	obj::face_point const &_face_point,
	Vertex const &_vertex)
{
	typedef typename
	boost::mpl::at
	<
		typename VertexFormatPart::elements,
		NormalIndex
	>::type
	normal_type;

	FCPPT_ASSERT_ERROR(
		_face_point.normal_index_);

	obj::normal const origin =
		_model.normals()[*_face_point.normal_index_];

	_vertex->template set<normal_type>(
		typename normal_type::packed_type(
			origin.n1_,
			origin.n2_,
			origin.n3_));
}
}
}
}
}
}

#endif
