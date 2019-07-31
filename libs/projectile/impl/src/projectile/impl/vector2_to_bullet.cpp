//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/vector2.hpp>
#include <sge/projectile/impl/vector2_to_bullet.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <fcppt/config/external_end.hpp>


btVector3
sge::projectile::impl::vector2_to_bullet(
	sge::projectile::vector2 const &_vector
)
{
	return
		btVector3(
			_vector.x(),
			_vector.y(),
			fcppt::literal<
				btScalar
			>(
				0
			)
		);
}
