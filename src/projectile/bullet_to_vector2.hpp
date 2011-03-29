#ifndef SGE_PROJECTILE_BULLET_TO_VECTOR2_HPP_INCLUDED
#define SGE_PROJECTILE_BULLET_TO_VECTOR2_HPP_INCLUDED

#include <sge/projectile/vector2.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <LinearMath/btVector3.h>

namespace sge
{
namespace projectile
{
vector2 const
bullet_to_vector2(
	btVector3 const &);
}
}

#endif
