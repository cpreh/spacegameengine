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


#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_NORMAL_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_NORMAL_HPP_INCLUDED

#include <sge/model/obj/face_point.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/void.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


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

	FCPPT_ASSERT_PRE(
		_face_point.normal_index_);

	FCPPT_ASSERT_ERROR(
		static_cast<obj::normal_sequence::size_type>(
			(*_face_point.normal_index_) - 1) < _model.normals().size());

	obj::normal const origin =
		_model.normals()[
			static_cast<obj::normal_sequence::size_type>(
				(*_face_point.normal_index_) - 1)];

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
