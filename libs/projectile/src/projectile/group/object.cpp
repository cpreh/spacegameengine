//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/world.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object.hpp>
#include <fcppt/literal.hpp>


sge::projectile::group::object::object(
	sge::projectile::world &_world
)
:
	category_(
		_world.next_group_id()
	),
	collides_(
		fcppt::literal<
			sge::projectile::group::id
		>(
			0
		)
	)
{
}

sge::projectile::group::object::~object()
= default;

void
sge::projectile::group::object::collides_with(
	sge::projectile::group::object const &_other
)
{
	collides_ |= _other.category_; // NOLINT(hicpp-signed-bitwise)
}
