#include <sge/projectile/ghost/scoped.hpp>
#include <sge/projectile/world.hpp>

sge::projectile::ghost::scoped::scoped(
	world &_world,
	object &_object,
	group::sequence const &_groups)
:
	world_(
		_world),
	object_(
		_object)
{
	world_.add_ghost(
		object_,
		_groups);
}

sge::projectile::ghost::scoped::~scoped()
{
	world_.remove_ghost(
		object_);
}
