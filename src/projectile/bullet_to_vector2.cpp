#include "bullet_to_vector2.hpp"

sge::projectile::vector2 const
sge::projectile::bullet_to_vector2(
	btVector3 const &v)
{
	return 
		vector2(
			v.getX(),
			v.getY());
}
