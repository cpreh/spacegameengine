//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GHOST_POSITION_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_POSITION_HPP_INCLUDED

#include <sge/projectile/vector2.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::projectile::ghost
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::projectile::vector2,
	position
);

}

#endif
