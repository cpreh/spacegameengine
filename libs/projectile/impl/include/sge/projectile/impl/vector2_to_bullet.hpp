//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_VECTOR2_TO_BULLET_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_VECTOR2_TO_BULLET_HPP_INCLUDED

#include <sge/projectile/vector2_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btVector3.h>
#include <fcppt/config/external_end.hpp>


namespace sge::projectile::impl
{

btVector3
vector2_to_bullet(
	sge::projectile::vector2 const &
);

}

#endif
