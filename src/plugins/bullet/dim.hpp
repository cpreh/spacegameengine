#ifndef SGE_BULLET_DIM_HPP_INCLUDED
#define SGE_BULLET_DIM_HPP_INCLUDED

#include "unit.hpp"
#include <fcppt/math/dim/static.hpp>

namespace sge
{
namespace bullet
{
typedef 
fcppt::math::dim::static_
<
	unit,
	3
>::type 
dim;
}
}

#endif
