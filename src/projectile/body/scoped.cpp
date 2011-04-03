#include <sge/projectile/body/scoped.hpp>
#include <sge/projectile/world.hpp>

sge::projectile::body::scoped::scoped(
	world &_world,
	object &_object,
	group::sequence const &_groups)
:
	world_(
		_world),
	object_(
		_object)
{
	world_.add_body(
		object_,
		_groups);
}

sge::projectile::body::scoped::~scoped()
{
	world_.remove_body(
		object_);
}
