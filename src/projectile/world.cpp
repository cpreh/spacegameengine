/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "declare_local_logger.hpp"
#include "ghost/detail/pair_callback.hpp"
#include <sge/projectile/world.hpp>
#include <sge/projectile/group/object.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/duration_output.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <limits>
#include <LinearMath/btVector3.h>
#include <LinearMath/btScalar.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("world"))

BOOST_STATIC_ASSERT((
	boost::is_same<btScalar,float>::value));

namespace
{
// The btPersistentManifold stores a void* to the collision
// object. This function makes a body out of it by following the
// various user_ptrs and casts.
sge::projectile::body::object &
void_ptr_to_body(
	void *a)
{
	FCPPT_ASSERT(
		a);

	btCollisionObject *co =
		static_cast<btCollisionObject *>(
			a);

	FCPPT_ASSERT(
		co->getUserPointer());

	return
		*static_cast<sge::projectile::body::object *>(
			co->getUserPointer());
}

// Determines if the void* in the persistent manifold is a ghost (this
// is the same that ghostobject::upcast does)
bool
is_ghost(
	void const * const obj)
{
	return
		static_cast<btCollisionObject const *>(
			obj)->getInternalType() == btCollisionObject::CO_GHOST_OBJECT;
}

// This functor is used to filter out the "valid" persistent
// manifolds. The rules are simple
// - we reject collisions where a ghost is involved (ghosts are by definition aabb overlap only, no narrow phase!)
// - just because a manifold is created doesn't mean the two objects collide, we have to inspect getNumContacts
bool
is_collision_manifold(
	btPersistentManifold *manifold)
{
	return
		manifold->getNumContacts() &&
		!is_ghost(
			manifold->getBody0()) &&
		!is_ghost(
			manifold->getBody1());
}
}

sge::projectile::world::world()
:
	body_collision_(),
	configuration_(
		fcppt::make_unique_ptr<btDefaultCollisionConfiguration>()),
	dispatcher_(
		fcppt::make_unique_ptr<btCollisionDispatcher>(
			configuration_.get())),
	broadphase_(
		fcppt::make_unique_ptr<btDbvtBroadphase>()),
	solver_(
		fcppt::make_unique_ptr<btSequentialImpulseConstraintSolver>()),
	world_(
		fcppt::make_unique_ptr<btDiscreteDynamicsWorld>(
			dispatcher_.get(),
			broadphase_.get(),
			solver_.get(),
			configuration_.get())),
	ghost_pair_callback_(
		fcppt::make_unique_ptr<ghost::detail::pair_callback>()),
	next_group_id_(
		static_cast<group::id>(
			1))
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("constructed world"));
	// bullet sets some default gravity
	world_->setGravity(
		btVector3(
			static_cast<btScalar>(
				0),
			static_cast<btScalar>(
				0),
			static_cast<btScalar>(
				0)));
	world_->setInternalTickCallback(
		&internal_tick_callback_static,
		this,
		// isPreTick
		false);
	broadphase_->getOverlappingPairCache()->setInternalGhostPairCallback(
		ghost_pair_callback_.get());
}

void
sge::projectile::world::update_discrete(
	time_increment const &delta,
	fixed_timestep const &fixed,
	maximum_substeps const &max_substeps)
{
	FCPPT_ASSERT_MESSAGE(
		max_substeps.get(),
		FCPPT_TEXT("If you want a variable timestep, use the other update function"));

	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("Doing a fixed simulation step with delta ")
			<< delta.get().count());

	world_->stepSimulation(
		delta.get().count(),
		// number of simulation substeps
		static_cast<int>(
			max_substeps.get()),
		fixed.get().count());
}

void
sge::projectile::world::update_continuous(
	time_increment const &delta)
{
	FCPPT_LOG_VERBOSE(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("Doing a variable simulation step with delta ")
			<< delta.get().count());

	world_->stepSimulation(
		delta.get().count(),
		// number of simulation substeps
		0);
}

void
sge::projectile::world::make_groups_collide(
	group::object &a,
	group::object &b)
{
	a.collides_with(
		b);
	b.collides_with(
		a);
}

fcppt::signal::auto_connection
sge::projectile::world::body_collision(
	body::collision const &f)
{
	return
		body_collision_.connect(
			f);
}

void
sge::projectile::world::add_body(
	body::object &_body,
	group::sequence const &_groups)
{
	group::id
		group = static_cast<group::id>(0),
		mask = group;

	for(
		group::sequence::const_iterator it(
			_groups.begin()
		);
		it != _groups.end();
		++it
	)
	{
		group |= it->get().category_;
		mask |= it->get().collides_;
	}

	world_->addRigidBody(
		_body.body_.get(),
		group,
		mask);
}

void
sge::projectile::world::remove_body(
	body::object &_body)
{
	world_->removeRigidBody(
		_body.body_.get());
}

void
sge::projectile::world::add_ghost(
	ghost::object &_ghost,
	group::sequence const &_groups)
{
	group::id
		group = static_cast<group::id>(0),
		mask = group;

	for(
		group::sequence::const_iterator it(
			_groups.begin()
		);
		it != _groups.end();
		++it
	)
	{
		group |= it->get().category_;
		mask |= it->get().collides_;
	}

	world_->addCollisionObject(
		_ghost.ghost_object_.get(),
		group,
		mask);
}

void
sge::projectile::world::remove_ghost(
	ghost::object &_ghost)
{
	world_->removeCollisionObject(
		_ghost.ghost_object_.get());
}

sge::projectile::world::~world()
{
}

sge::projectile::group::id
sge::projectile::world::next_group_id()
{
	FCPPT_ASSERT_MESSAGE(
		next_group_id_ != std::numeric_limits<group::id>::max(),
		FCPPT_TEXT("You have created too many groups. Bummer. :/"));
	group::id const old = next_group_id_;
	// <<= doesn't work because of -Wconversion
	next_group_id_ =
		static_cast<group::id>(
			next_group_id_ << 1);
	return old;
}

void
sge::projectile::world::internal_tick_callback_static(
	btDynamicsWorld *w,
	btScalar const time_step)
{
	FCPPT_ASSERT(
		w->getWorldUserInfo());

	static_cast<world *>(
		w->getWorldUserInfo())->internal_tick_callback(
		time_step);
}

void
sge::projectile::world::internal_tick_callback(
	btScalar /* time_step */)
{
	for(
		btPersistentManifold **current_manifold =
			world_->getDispatcher()->getInternalManifoldPointer()
		,
		**manifold_end =
				world_->getDispatcher()->getInternalManifoldPointer() +
				world_->getDispatcher()->getNumManifolds()
		;
		current_manifold != manifold_end;
		++current_manifold
	)
	{
		if(
			!is_collision_manifold(
				*current_manifold
			)
		)
			continue;

		FCPPT_LOG_VERBOSE(
			local_log,
			fcppt::log::_ << FCPPT_TEXT("There has been a collision between two bodies"));
		body_collision_(
			void_ptr_to_body(
				(*current_manifold)->getBody0()),
			void_ptr_to_body(
				(*current_manifold)->getBody1()));

		// For additional data:
		/*
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
		*/
	}
}
