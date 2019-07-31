//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/vector2.hpp>
#include <sge/projectile/impl/bullet_to_vector2.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btVector3.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::vector2
sge::projectile::impl::bullet_to_vector2(
	btVector3 const &_vector
)
{
	return
		sge::projectile::vector2{
			_vector.getX(),
			_vector.getY()
		};
}
