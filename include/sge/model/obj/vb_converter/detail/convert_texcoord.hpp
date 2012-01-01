/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_TEXCOORD_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_TEXCOORD_HPP_INCLUDED

#include <sge/model/obj/face_point.hpp>
#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
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

	FCPPT_ASSERT_PRE(
		_face_point.texcoord_index_);

	FCPPT_ASSERT_ERROR(
		static_cast<obj::texcoord_sequence::size_type>(
			(*_face_point.texcoord_index_) - 1) < _model.texcoords().size());

	obj::texcoord const origin =
		_model.texcoords()[
			static_cast<obj::texcoord_sequence::size_type>(
				(*_face_point.texcoord_index_) - 1)];

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
