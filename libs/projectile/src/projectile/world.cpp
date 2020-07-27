//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/log.hpp>
#include <sge/projectile/world.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/object_ref.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/group/object.hpp>
#include <sge/projectile/group/object_ref.hpp>
#include <sge/projectile/impl/collision_tester.hpp>
#include <sge/projectile/impl/ghost/detail/pair_callback.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/pre_message.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <limits>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


static_assert(
	std::is_same<btScalar,float>::value,
	"btScalar is expected to be float");

namespace
{
sge::projectile::body::object const &
void_ptr_to_body(
	btCollisionObject const *co)
{
	FCPPT_ASSERT_PRE(
		co->getUserPointer());

	return
		*static_cast<sge::projectile::body::object const *>(
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
		manifold->getNumContacts() != 0 &&
		!is_ghost(
			manifold->getBody0()) &&
		!is_ghost(
			manifold->getBody1());
}
}

sge::projectile::world::world(
	sge::projectile::log const &_log
)
:
	log_{
		_log.world_log()
	},
	body_collision_(),
	configuration_(
		fcppt::unique_ptr_to_base<
			btCollisionConfiguration
		>(
			fcppt::make_unique_ptr<
				btDefaultCollisionConfiguration
			>()
		)
	),
	dispatcher_(
		fcppt::make_unique_ptr<btCollisionDispatcher>(
			configuration_.get_pointer())),
	broadphase_(
		fcppt::unique_ptr_to_base<
			btBroadphaseInterface
		>(
			fcppt::make_unique_ptr<
				btDbvtBroadphase
			>()
		)
	),
	solver_(
		fcppt::unique_ptr_to_base<
			btConstraintSolver
		>(
			fcppt::make_unique_ptr<
				btSequentialImpulseConstraintSolver
			>()
		)
	),
	world_(
		fcppt::make_unique_ptr<btDiscreteDynamicsWorld>(
			dispatcher_.get_pointer(),
			broadphase_.get_pointer(),
			solver_.get_pointer(),
			configuration_.get_pointer())),
	ghost_pair_callback_(
		fcppt::make_unique_ptr<ghost::detail::pair_callback>()),
	next_group_id_(
		static_cast<group::id>(
			1))
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out << FCPPT_TEXT("constructed world")
	)

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
		ghost_pair_callback_.get_pointer());
}

void
sge::projectile::world::update_discrete(
	time_increment const &delta,
	fixed_timestep const &fixed,
	maximum_substeps const &max_substeps)
{
	FCPPT_ASSERT_PRE_MESSAGE(
		max_substeps.get(),
		FCPPT_TEXT("If you want a variable timestep, use the other update function"));

	FCPPT_LOG_VERBOSE(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("Doing a fixed simulation step with delta ")
			<< delta.get().count()
	)

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
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("Doing a variable simulation step with delta ")
			<< delta.get().count()
	)

	world_->stepSimulation(
		delta.get().count(),
		// number of simulation substeps
		0);
}

void
sge::projectile::world::make_groups_collide( // NOLINT(readability-convert-member-functions-to-static)
	sge::projectile::group::object &_a,
	sge::projectile::group::object &_b
)
{
	_a.collides_with(
		_b
	);

	_b.collides_with(
		_a
	);
}

fcppt::signal::auto_connection
sge::projectile::world::body_collision(
	sge::projectile::body::collision &&f
)
{
	return
		body_collision_.connect(
			std::move(
				f
			)
		);
}

void
sge::projectile::world::add_body(
	sge::projectile::body::object_ref const _body,
	sge::projectile::group::sequence const &_groups
)
{
	auto group = static_cast<sge::projectile::group::id>(0);
	sge::projectile::group::id mask = group;

	for(
		auto const &cur
		:
		_groups
	)
	{
		group = static_cast<sge::projectile::group::id>(group | cur.get().category_); // NOLINT(hicpp-signed-bitwise)
		mask = static_cast<sge::projectile::group::id>(mask | cur.get().collides_); // NOLINT(hicpp-signed-bitwise)
	}

	world_->addRigidBody(
		_body.get().body_.get_pointer(),
		group,
		mask
	);
}

void
sge::projectile::world::remove_body(
	sge::projectile::body::object &_body
)
{
	world_->removeRigidBody(
		_body.body_.get_pointer());
}

void
sge::projectile::world::add_ghost(
	sge::projectile::ghost::object_ref const _ghost,
	sge::projectile::group::sequence const &_groups
)
{
	auto group = static_cast<group::id>(0);
	sge::projectile::group::id mask = group;

	// TODO(philipp): unify this with add_body
	for(
		auto const &cur_group
		:
		_groups
	)
	{
		group = static_cast<sge::projectile::group::id>(group | cur_group.get().category_); // NOLINT(hicpp-signed-bitwise)
		mask = static_cast<sge::projectile::group::id>(mask | cur_group.get().collides_); // NOLINT(hicpp-signed-bitwise)
	}

	world_->addCollisionObject(
		_ghost.get().ghost_object_.get_pointer(),
		group,
		mask);
}

void
sge::projectile::world::remove_ghost(
	sge::projectile::ghost::object &_ghost
)
{
	world_->removeCollisionObject(
		_ghost.ghost_object_.get_pointer());
}

bool
sge::projectile::world::collides(
	sge::projectile::body::object const &_body_a,
	sge::projectile::body::object const &_body_b
) const
{
	sge::projectile::impl::collision_tester tester;

	world_->contactPairTest(
		_body_a.body_.get_pointer(),
		_body_b.body_.get_pointer(),
		tester
	);

	return
		tester.result();
}

sge::projectile::world::~world()
= default;

sge::projectile::group::id
sge::projectile::world::next_group_id()
{
	FCPPT_ASSERT_PRE_MESSAGE(
		next_group_id_ != std::numeric_limits<group::id>::max(),
		FCPPT_TEXT("You have created too many groups. Bummer. :/"));
	group::id const old = next_group_id_;
	// <<= doesn't work because of -Wconversion
	next_group_id_ =
		static_cast<group::id>(
			next_group_id_ << 1); // NOLINT(hicpp-signed-bitwise)
	return old;
}

void
sge::projectile::world::internal_tick_callback_static(
	btDynamicsWorld *w,
	btScalar const time_step)
{
	FCPPT_ASSERT_PRE(
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
				world_->getDispatcher()->getInternalManifoldPointer() + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				world_->getDispatcher()->getNumManifolds()
		;
		current_manifold != manifold_end;
		++current_manifold // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
	)
	{
		if(
			!is_collision_manifold(
				*current_manifold
			)
		)
		{
			continue;
		}

		FCPPT_LOG_VERBOSE(
			log_,
			fcppt::log::out << FCPPT_TEXT("There has been a collision between two bodies")
		)

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
