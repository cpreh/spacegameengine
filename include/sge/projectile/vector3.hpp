#ifndef SGE_PROJECTILE_VECTOR3_HPP_INCLUDED
#define SGE_PROJECTILE_VECTOR3_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace projectile
{
typedef
fcppt::math::vector::static_
<
	scalar,
	3
>::type
vector3;
}
}

#endif
