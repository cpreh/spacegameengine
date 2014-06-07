/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PROJECTILE_WORLD_HPP_INCLUDED
#define SGE_PROJECTILE_WORLD_HPP_INCLUDED

#include <sge/projectile/fixed_timestep.hpp>
#include <sge/projectile/maximum_substeps.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/body/collision.hpp>
#include <sge/projectile/body/collision_fn.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/detail/debug_drawer_impl_fwd.hpp>
#include <sge/projectile/ghost/object_fwd.hpp>
#include <sge/projectile/ghost/detail/pair_callback_fwd.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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
	SGE_PROJECTILE_SYMBOL
	world();

	SGE_PROJECTILE_SYMBOL void
	update_discrete(
		time_increment const &,
		fixed_timestep const &,
		maximum_substeps const &);

	SGE_PROJECTILE_SYMBOL void
	update_continuous(
		time_increment const &);

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

	SGE_PROJECTILE_SYMBOL
	bool
	collides(
		sge::projectile::body::object const &,
		sge::projectile::body::object const &
	) const;

	SGE_PROJECTILE_SYMBOL ~world();
private:
	friend class sge::projectile::group::object;
	friend class sge::projectile::detail::debug_drawer_impl;

	fcppt::signal::object<body::collision_fn> body_collision_;
	std::unique_ptr<btCollisionConfiguration> const configuration_;
	std::unique_ptr<btCollisionDispatcher> const dispatcher_;
	std::unique_ptr<btBroadphaseInterface> const broadphase_;
	std::unique_ptr<btConstraintSolver> const solver_;
	// This is not a btDynamicsWorld because btDynamicsWorld doesn't
	// have addRigidBody with group and mask parameter.
	std::unique_ptr<btDiscreteDynamicsWorld> const world_;
	std::unique_ptr<ghost::detail::pair_callback> const ghost_pair_callback_;
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
