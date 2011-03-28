#include <sge/projectile/body/parameters.hpp>

sge::projectile::body::parameters::parameters(
	sge::projectile::world &_world,
	sge::projectile::body::position const &_position,
	sge::projectile::body::linear_velocity const &_linear_velocity,
	sge::projectile::body::angular_velocity const &_angular_velocity,
	sge::projectile::shape::shared_base_ptr const &_shape,
	sge::projectile::body::rotation const &_rotation,
	sge::projectile::body::solidity::variant const &_solidity,
	sge::projectile::group::sequence const &_groups,
	sge::projectile::body::user_data const &_user_data)
:
	world_(
		_world),
	position_(
		_position),
	linear_velocity_(
		_linear_velocity),
	angular_velocity_(
		_angular_velocity),
	shape_(
		_shape),
	rotation_(
		_rotation),
	solidity_(
		_solidity),
	groups_(
		_groups),
	user_data_(
		_user_data)
{
}

sge::projectile::world &
sge::projectile::body::parameters::world() const
{
	return world_;
}

sge::projectile::body::position const &
sge::projectile::body::parameters::position() const
{
	return position_;
}

sge::projectile::body::linear_velocity const &
sge::projectile::body::parameters::linear_velocity() const
{
	return linear_velocity_;
}

sge::projectile::body::angular_velocity const &
sge::projectile::body::parameters::angular_velocity() const
{
	return angular_velocity_;
}

sge::projectile::shape::shared_base_ptr const &
sge::projectile::body::parameters::shape() const
{
	return shape_;
}

sge::projectile::body::rotation const &
sge::projectile::body::parameters::rotation() const
{
	return rotation_;
}

sge::projectile::body::solidity::variant const &
sge::projectile::body::parameters::solidity() const
{
	return solidity_;
}

sge::projectile::group::sequence const &
sge::projectile::body::parameters::groups() const
{
	return groups_;
}

sge::projectile::body::user_data const &
sge::projectile::body::parameters::user_data() const
{
	return user_data_;
}
