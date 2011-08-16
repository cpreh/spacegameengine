#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_FACE_POINT_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_FACE_POINT_HPP_INCLUDED

#include <sge/model/obj/face_point.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/vertex_sequence.hpp>
#include <sge/model/obj/vb_converter/roles/position.hpp>
#include <sge/model/obj/vb_converter/detail/convert_vertex.hpp>
#include <sge/model/obj/vb_converter/detail/convert_texcoord.hpp>
#include <sge/model/obj/vb_converter/detail/convert_normal.hpp>
#include <sge/model/obj/vb_converter/roles/texcoord.hpp>
#include <sge/model/obj/vb_converter/roles/normal.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <fcppt/assert/error.hpp>
#include <boost/mpl/at.hpp>

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
convert_face_point(
	obj::instance const &_model,
	obj::face_point const &_face_point,
	VertexIterator &_current_vertex)
{
	typedef typename
	boost::mpl::at
	<
		PositionMap,
		vb_converter::roles::position
	>::type
	position_index_type;

	typedef typename
	boost::mpl::at
	<
		typename VertexFormatPart::elements,
		position_index_type
	>::type
	position_type;

	FCPPT_ASSERT_ERROR(
		static_cast<obj::vertex_sequence::size_type>(
			_face_point.vertex_index_ - 1) < _model.vertices().size());

	_current_vertex->template set<position_type>(
		detail::convert_vertex<typename position_type::packed_type>(
			// Attention: indices in obj are 1-based!
			_model.vertices()[
				static_cast<obj::vertex_sequence::size_type>(
					_face_point.vertex_index_ - 1)]));

	typedef typename
	boost::mpl::at
	<
		PositionMap,
		vb_converter::roles::texcoord
	>::type
	texcoord_index_type;

	detail::convert_texcoord<texcoord_index_type,VertexFormatPart>(
		_model,
		_face_point,
		_current_vertex);

	typedef typename
	boost::mpl::at
	<
		PositionMap,
		vb_converter::roles::normal
	>::type
	normal_index_type;

	detail::convert_normal<normal_index_type,VertexFormatPart>(
		_model,
		_face_point,
		_current_vertex);

	++_current_vertex;
}
}
}
}
}
}

#endif
