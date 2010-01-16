#ifndef SGE_BULLET_CONVERT_POINT_TO_SGE_HPP_INCLUDED
#define SGE_BULLET_CONVERT_POINT_TO_SGE_HPP_INCLUDED

#include "../point.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <LinearMath/btVector3.h>

namespace sge
{
namespace bullet
{
namespace convert
{
inline sge::bullet::point const 
point_to_sge(
	btVector3 const &v)
{
	return 
		point(
			v.x(),
			v.y(),
			v.z());
}
}
}
}

#endif
