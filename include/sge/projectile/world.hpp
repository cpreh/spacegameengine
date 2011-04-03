#ifndef SGE_PROJECTILE_WORLD_HPP_INCLUDED
#define SGE_PROJECTILE_WORLD_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/body/collision.hpp>
#include <sge/projectile/body/collision_fn.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/ghost/detail/pair_callback_fwd.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/time/duration.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>

class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;
class btDiscreteDynamicsWorld;
class btDynamicsWorld;

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

	SGE_PROJECTILE_SYMBOL void
	add_body(
		body::object &,
		group::sequence const &);

	SGE_PROJECTILE_SYMBOL void
	remove_body(
		body::object &);

	SGE_PROJECTILE_SYMBOL void
	add_ghost(
		ghost::object &,
		group::sequence const &);

	SGE_PROJECTILE_SYMBOL void
	remove_ghost(
		ghost::object &);

	SGE_PROJECTILE_SYMBOL ~world();
private:
	friend class sge::projectile::group::object;
	friend class sge::projectile::detail::debug_drawer_impl;

	fcppt::signal::object<body::collision_fn> body_collision_;
	fcppt::scoped_ptr<btCollisionConfiguration> configuration_;
	fcppt::scoped_ptr<btCollisionDispatcher> dispatcher_;
	fcppt::scoped_ptr<btBroadphaseInterface> broadphase_;
	fcppt::scoped_ptr<btConstraintSolver> solver_;
	// This is not a btDynamicsWorld because btDynamicsWorld doesn't
	// have addRigidBody with group and mask parameter.
	fcppt::scoped_ptr<btDiscreteDynamicsWorld> world_;
	fcppt::scoped_ptr<ghost::detail::pair_callback> ghost_pair_callback_;
	group::id next_group_id_;

	// for group
	group::id
	next_group_id();

	static void
	internal_tick_callback_static(
		btDynamicsWorld *,
		scalar);

	void
	internal_tick_callback(
		scalar);
};
}
}

#endif
