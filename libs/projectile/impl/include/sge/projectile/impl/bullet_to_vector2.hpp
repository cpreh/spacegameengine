//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_BULLET_TO_VECTOR2_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_BULLET_TO_VECTOR2_HPP_INCLUDED

#include <sge/projectile/vector2.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btVector3.h>
#include <fcppt/config/external_end.hpp>


namespace sge::projectile::impl
{

sge::projectile::vector2
bullet_to_vector2(
	btVector3 const &
);

}

#endif
