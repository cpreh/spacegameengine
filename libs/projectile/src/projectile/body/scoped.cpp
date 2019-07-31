//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/world.hpp>
#include <sge/projectile/body/scoped.hpp>


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
