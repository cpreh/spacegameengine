#ifndef SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_VERTEX_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_DETAIL_CONVERT_VERTEX_HPP_INCLUDED

#include <sge/model/obj/vertex.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/is_static_size.hpp>
#include <boost/type_traits/integral_constant.hpp>

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
