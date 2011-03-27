#include <sge/projectile/ghost/parameters.hpp>

sge::projectile::ghost::parameters::parameters(
	sge::projectile::world &_world,
	sge::projectile::ghost::position const &_position,
	sge::projectile::ghost::size const &_size,
	sge::projectile::group::sequence const &_groups,
	sge::projectile::ghost::user_data const &_user_data)
:
	world_(
		_world),
	position_(
		_position),
	size_(
		_size),
	groups_(
		_groups),
	user_data_(
		_user_data)
{
}

sge::projectile::world &
sge::projectile::ghost::parameters::world() const
{
	return world_;
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

sge::projectile::group::sequence const &
sge::projectile::ghost::parameters::groups() const
{
	return groups_;
}

sge::projectile::ghost::user_data const &
sge::projectile::ghost::parameters::user_data() const
{
	return user_data_;
}
