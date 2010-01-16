#ifndef SGE_BULLET_POINT_HPP_INCLUDED
#define SGE_BULLET_POINT_HPP_INCLUDED

#include "unit.hpp"
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace bullet
{
typedef 
fcppt::math::vector::static_
<
	unit,
	3
>::type point;
}
}

#endif
