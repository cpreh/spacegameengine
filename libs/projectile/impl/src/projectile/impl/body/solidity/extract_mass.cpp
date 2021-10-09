//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/body/solidity/static.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/impl/body/solidity/extract_mass.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <fcppt/config/external_end.hpp>

btScalar sge::projectile::impl::body::solidity::extract_mass(
    sge::projectile::body::solidity::variant const &_solidity)
{
  return fcppt::variant::match(
      _solidity,
      [](sge::projectile::body::solidity::static_ const &) { return fcppt::literal<btScalar>(0); },
      [](sge::projectile::body::solidity::solid const &_solid) { return _solid.mass().get(); },
      [](sge::projectile::body::solidity::nonsolid const &)
      { return fcppt::literal<btScalar>(1); });
}
