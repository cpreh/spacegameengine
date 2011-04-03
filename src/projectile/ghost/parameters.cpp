#include <sge/projectile/ghost/parameters.hpp>

sge::projectile::ghost::parameters::parameters(
	sge::projectile::ghost::position const &_position,
	sge::projectile::ghost::size const &_size)
:
	position_(
		_position),
	size_(
		_size)
{
}

sge::projectile::ghost::position const &
sge::projectile::ghost::parameters::position() const
{
	return position_;
}

sge::projectile::ghost::size const &
sge::projectile::ghost::parameters::size() const
{
	return size_;
}
