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
