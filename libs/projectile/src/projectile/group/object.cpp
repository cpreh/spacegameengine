//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/world.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object.hpp>


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
