//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/impl/ghost/detail/pair_callback.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <fcppt/config/external_end.hpp>


sge::projectile::ghost::detail::pair_callback::pair_callback()
{
}

sge::projectile::ghost::detail::pair_callback::~pair_callback()
{
}

btBroadphasePair *
sge::projectile::ghost::detail::pair_callback::addOverlappingPair(
	btBroadphaseProxy *proxy0,
	btBroadphaseProxy *proxy1)
{
	btCollisionObject
		*col_obj0 =
			static_cast<btCollisionObject*>(
				proxy0->m_clientObject),
		*col_obj1 =
			static_cast<btCollisionObject*>(
				proxy1->m_clientObject);

	btGhostObject
		*ghost0 =
			btGhostObject::upcast(
				col_obj0),
		*ghost1 =
			btGhostObject::upcast(
				col_obj1);

	// FIXME: ASSERT
	if (ghost0)
	{
		if(!ghost1)
		{
			FCPPT_ASSERT_ERROR(
				ghost0->getUserPointer());
			void *user_pointer0 =
				ghost0->getUserPointer();
			FCPPT_ASSERT_ERROR(
				col_obj1);
			FCPPT_ASSERT_ERROR(
				col_obj1->getUserPointer());
			void *user_pointer1 =
				col_obj1->getUserPointer();

			static_cast<object *>(user_pointer0)->enter_internal(
				*static_cast<body::object const *>(
					user_pointer1));
		}
		ghost0->addOverlappingObjectInternal(
			proxy1,
			proxy0);
	}

	if (ghost1)
	{
		if(!ghost0)
		{
			FCPPT_ASSERT_ERROR(
				ghost1->getUserPointer());
			void *user_pointer1 =
				ghost1->getUserPointer();
			FCPPT_ASSERT_ERROR(
				col_obj0);
			FCPPT_ASSERT_ERROR(
				col_obj0->getUserPointer());
			void *user_pointer0 =
				col_obj0->getUserPointer();

			static_cast<object *>(user_pointer1)->enter_internal(
				*static_cast<body::object const *>(
					user_pointer0));
		}

		ghost1->addOverlappingObjectInternal(
			proxy0,
			proxy1);
	}

	return nullptr;
}

void*
sge::projectile::ghost::detail::pair_callback::removeOverlappingPair(
	btBroadphaseProxy *proxy0,
	btBroadphaseProxy *proxy1,
	btDispatcher *dispatcher)
{
	btCollisionObject
		*col_obj0 =
			static_cast<btCollisionObject*>(
				proxy0->m_clientObject),
		*col_obj1 =
			static_cast<btCollisionObject*>(
				proxy1->m_clientObject);

	btGhostObject
		*ghost0 =
			btGhostObject::upcast(
				col_obj0),
		*ghost1 =
			btGhostObject::upcast(
				col_obj1);

	if (ghost0)
	{
		if(!ghost1)
		{
			FCPPT_ASSERT_ERROR(
				ghost0->getUserPointer());
			void *user_pointer0 =
				ghost0->getUserPointer();
			FCPPT_ASSERT_ERROR(
				col_obj1);
			FCPPT_ASSERT_ERROR(
				col_obj1->getUserPointer());
			void *user_pointer1 =
				col_obj1->getUserPointer();

			static_cast<object *>(user_pointer0)->exit_internal(
				*static_cast<body::object const *>(
					user_pointer1));
		}
		ghost0->removeOverlappingObjectInternal(
			proxy1,
			dispatcher,
			proxy0);
	}

	if (ghost1)
	{
		if(!ghost0)
		{
			FCPPT_ASSERT_ERROR(
				ghost1->getUserPointer());
			void *user_pointer1 =
				ghost1->getUserPointer();
			FCPPT_ASSERT_ERROR(
				col_obj0);
			FCPPT_ASSERT_ERROR(
				col_obj0->getUserPointer());
			void *user_pointer0 =
				col_obj0->getUserPointer();

			static_cast<object *>(user_pointer1)->exit_internal(
				*static_cast<body::object const *>(
					user_pointer0));
		}
		ghost1->removeOverlappingObjectInternal(
			proxy0,
			dispatcher,
			proxy1);
	}

	return nullptr;
}

void
sge::projectile::ghost::detail::pair_callback::removeOverlappingPairsContainingProxy(
	btBroadphaseProxy*,
	btDispatcher*)
{
	FCPPT_ASSERT_UNREACHABLE;
}
