#ifndef SGE_PROJECTILE_VECTOR2_TO_BULLET_HPP_INCLUDED
#define SGE_PROJECTILE_VECTOR2_TO_BULLET_HPP_INCLUDED

#include <LinearMath/btVector3.h>
#include <sge/projectile/vector2.hpp>

namespace sge
{
namespace projectile
{
btVector3 const
vector2_to_bullet(
	vector2 const &);
}
}

#endif
