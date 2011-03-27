#ifndef SGE_PROJECTILE_WORLD_HPP_INCLUDED
#define SGE_PROJECTILE_WORLD_HPP_INCLUDED

#include <sge/projectile/body/collision.hpp>
#include <sge/projectile/body/collision_fn.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/ghost/detail/pair_callback.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/projectile/debug_drawer_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/time/duration.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

namespace sge
{
namespace projectile
{
class world
{
FCPPT_NONCOPYABLE(
	world);
public:
	SGE_PROJECTILE_SYMBOL explicit
	world();

	SGE_PROJECTILE_SYMBOL void
	update(
		sge::time::duration const &);

	SGE_PROJECTILE_SYMBOL void
	make_groups_collide(
		group::object &,
		group::object &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	body_collision(
		body::collision const &);

	SGE_PROJECTILE_SYMBOL ~world();
private:
	friend class sge::projectile::body::object;
	friend class sge::projectile::ghost::object;
	friend class sge::projectile::group::object;
	friend class sge::projectile::debug_drawer;

	fcppt::signal::object<body::collision_fn> body_collision_;
	btDefaultCollisionConfiguration configuration_;
	btCollisionDispatcher dispatcher_;
	btDbvtBroadphase broadphase_;
	btSequentialImpulseConstraintSolver solver_;
	btDiscreteDynamicsWorld world_;
	ghost::detail::pair_callback ghost_pair_callback_;
	group::id next_group_id_;

	// for group
	group::id
	next_group_id();

	static void
	internal_tick_callback_static(
		btDynamicsWorld *,
		btScalar);

	void
	internal_tick_callback(
		btScalar);
};
}
}

#endif
