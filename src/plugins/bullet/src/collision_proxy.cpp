#include "../collision_proxy.hpp"

sge::bullet::collision_proxy::collision_proxy(
	shapes::base &a,
	shapes::base &b,
	sge::bullet::world &_world)
:
	shapes_(
		std::make_pair(
			&a,
			&b)),
	world_(
		&_world)
{
}

bool 
sge::bullet::collision_proxy::operator<(
	collision_proxy const &rhs) const
{
	return 
		shapes_ < rhs.shapes_;
}

sge::bullet::collision_proxy::shape_pair const &
sge::bullet::collision_proxy::shapes() const
{
	return 
		shapes_;
}

sge::bullet::world &
sge::bullet::collision_proxy::world() const
{
	return 
		*world_;
}
