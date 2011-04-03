#include <sge/projectile/group/object.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/world.hpp>

sge::projectile::group::object::object(
	world &_world)
:
	category_(
		_world.next_group_id()),
	collides_(
		// a valid static_cast since id is short! Winning.
		static_cast<id>(
			0))
{
}

sge::projectile::group::object::~object()
{
}

void
sge::projectile::group::object::collides_with(
	object const &other)
{
	collides_ |= other.category_;
}
