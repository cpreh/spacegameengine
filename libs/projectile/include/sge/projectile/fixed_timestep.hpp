//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_FIXED_TIMESTEP_HPP_INCLUDED
#define SGE_PROJECTILE_FIXED_TIMESTEP_HPP_INCLUDED

#include <sge/projectile/duration.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::projectile
{

FCPPT_DECLARE_STRONG_TYPEDEF(sge::projectile::duration, fixed_timestep);

}

#endif
