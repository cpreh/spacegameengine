//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/body/solidity/solid.hpp>


sge::projectile::body::solidity::solid::solid(
	sge::projectile::body::mass const &_mass)
:
	mass_(
		_mass)
{
}

sge::projectile::body::mass const &
sge::projectile::body::solidity::solid::mass() const
{
	return mass_;
}
