//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GHOST_OBJECT_REF_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_OBJECT_REF_HPP_INCLUDED

#include <sge/projectile/ghost/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::projectile::ghost
{

using
object_ref
=
fcppt::reference<
	sge::projectile::ghost::object
>;

}

#endif
