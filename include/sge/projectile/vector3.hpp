#ifndef SGE_PROJECTILE_VECTOR3_HPP_INCLUDED
#define SGE_PROJECTILE_VECTOR3_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>
#include <bullet/LinearMath/btScalar.h>

namespace sge
{
namespace projectile
{
typedef
fcppt::math::vector::static_
<
	btScalar,
	3
>::type
vector3;
}
}

#endif
