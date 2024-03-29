//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_IMPL_BODY_SOLIDITY_EXTRACT_MASS_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_BODY_SOLIDITY_EXTRACT_MASS_HPP_INCLUDED

#include <sge/projectile/body/solidity/variant_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <fcppt/config/external_end.hpp>

namespace sge::projectile::impl::body::solidity
{

btScalar extract_mass(sge::projectile::body::solidity::variant const &);

}

#endif
