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


#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_VERTEX_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_VERTEX_HPP_INCLUDED

#include <sge/model/obj/vertex.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/is_static_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/integral_constant.hpp>
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
template<typename TargetVector>
typename
boost::enable_if
<
	boost::mpl::and_
	<
		fcppt::math::is_static_size<typename TargetVector::dim_wrapper>,
		boost::integral_constant<bool,TargetVector::dim_wrapper::value >= 3>
	>,
	TargetVector
>::type const
convert_vertex(
	obj::vertex const &v)
{
	TargetVector result;

	result[0] = v.v1_;
	result[1] = v.v2_;
	result[2] = v.v3_;

	// Instead of a runtime if, this could be a compile time if, of
	// course. But I was lazy and didn't think it mattered much (what
	// with optimizing and all).
	if(result.size() == 4)
		result[3] = *v.v4_;

	return result;
}
}
}
}
}
}

#endif
