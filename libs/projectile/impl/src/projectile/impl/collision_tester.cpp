//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/impl/collision_tester.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::impl::collision_tester::collision_tester()
:
	result_(
		false
	)
{
}

sge::projectile::impl::collision_tester::~collision_tester()
= default;

bool
sge::projectile::impl::collision_tester::result() const
{
	return
		result_;
}

bool
sge::projectile::impl::collision_tester::needsCollision(
	btBroadphaseProxy *
) const
{
	return
		true;
}

btScalar
sge::projectile::impl::collision_tester::addSingleResult(
	btManifoldPoint &,
	btCollisionObjectWrapper const *,
	int,
	int,
	btCollisionObjectWrapper const *,
	int,
	int
)
{
	result_ = true;

	return 0.F; // wtf?
}
