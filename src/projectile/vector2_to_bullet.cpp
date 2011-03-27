#include "vector2_to_bullet.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

btVector3 const
sge::projectile::vector2_to_bullet(
	vector2 const &v)
{
	return 
		btVector3(
			v[0],
			v[1],
			static_cast<btScalar>(0));
}
