//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_WORLD_HPP_INCLUDED
#define SGE_PROJECTILE_WORLD_HPP_INCLUDED

#include <sge/projectile/fixed_timestep.hpp>
#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/maximum_substeps.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/body/collision.hpp>
#include <sge/projectile/body/collision_fn.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/ghost/detail/pair_callback_fwd.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


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
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	world(
		sge::projectile::log const &
	);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	update_discrete(
		time_increment const &,
		fixed_timestep const &,
		maximum_substeps const &);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	update_continuous(
		time_increment const &);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	make_groups_collide(
		group::object &,
		group::object &);

	SGE_PROJECTILE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	body_collision(
		sge::projectile::body::collision &&
	);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	add_body(
		body::object &,
		group::sequence const &);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	remove_body(
		body::object &);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	add_ghost(
		ghost::object &,
		group::sequence const &);

	SGE_PROJECTILE_DETAIL_SYMBOL void
	remove_ghost(
		ghost::object &);

	SGE_PROJECTILE_DETAIL_SYMBOL
	bool
	collides(
		sge::projectile::body::object const &,
		sge::projectile::body::object const &
	) const;

	SGE_PROJECTILE_DETAIL_SYMBOL ~world();
private:
	friend class sge::projectile::group::object;
	friend class sge::projectile::detail::debug_drawer_impl;

	fcppt::log::object &log_;
	fcppt::signal::object<body::collision_fn> body_collision_;
	fcppt::unique_ptr<btCollisionConfiguration> const configuration_;
	fcppt::unique_ptr<btCollisionDispatcher> const dispatcher_;
	fcppt::unique_ptr<btBroadphaseInterface> const broadphase_;
	fcppt::unique_ptr<btConstraintSolver> const solver_;
	// This is not a btDynamicsWorld because btDynamicsWorld doesn't
	// have addRigidBody with group and mask parameter.
	fcppt::unique_ptr<btDiscreteDynamicsWorld> const world_;
	fcppt::unique_ptr<ghost::detail::pair_callback> const ghost_pair_callback_;
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
