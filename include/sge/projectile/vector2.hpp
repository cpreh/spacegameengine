#ifndef SGE_PROJECTILE_VECTOR2_HPP_INCLUDED
#define SGE_PROJECTILE_VECTOR2_HPP_INCLUDED

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
	2
>::type
vector2;
}
}

#endif
