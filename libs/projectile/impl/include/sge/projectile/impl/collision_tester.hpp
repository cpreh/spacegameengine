//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_COLLISION_TESTER_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_COLLISION_TESTER_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace impl
{

class collision_tester
:
	public btCollisionWorld::ContactResultCallback
{
	FCPPT_NONCOPYABLE(
		collision_tester
	);
public:
	collision_tester();

	~collision_tester()
	override;

	bool
	result() const;
private:
	bool
	needsCollision(
		btBroadphaseProxy *
	) const
	override;

	btScalar
	addSingleResult(
		btManifoldPoint &,
		btCollisionObjectWrapper const *colObj0Wrap,
		int partId0,
		int index0,
		btCollisionObjectWrapper const *colObj1Wrap,
		int partId1,
		int index1
	)
	override;

	bool result_;
};

}
}
}

#endif
