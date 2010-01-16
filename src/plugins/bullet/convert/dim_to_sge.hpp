#ifndef SGE_BULLET_CONVERT_DIM_TO_SGE_HPP_INCLUDED
#define SGE_BULLET_CONVERT_DIM_TO_SGE_HPP_INCLUDED

#include "../dim.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <LinearMath/btVector3.h>

namespace sge
{
namespace bullet
{
namespace convert
{
inline sge::bullet::dim const 
dim_to_sge(
	btVector3 const &v)
{
	return 
		dim(
			v.x(),
			v.y(),
			v.z());
}
}
}
}

#endif
