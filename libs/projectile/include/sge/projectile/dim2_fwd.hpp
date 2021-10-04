//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_DIM2_FWD_HPP_INCLUDED
#define SGE_PROJECTILE_DIM2_FWD_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <fcppt/math/dim/static_fwd.hpp>


namespace sge::projectile
{

using
dim2
=
fcppt::math::dim::static_<
	sge::projectile::scalar,
	2
>;

}

#endif
