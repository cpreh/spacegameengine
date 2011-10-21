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


#include "pair_callback.hpp"
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <fcppt/config/external_end.hpp>


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

	return 0;
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

	return 0;
}

void
sge::projectile::ghost::detail::pair_callback::removeOverlappingPairsContainingProxy(
	btBroadphaseProxy*,
	btDispatcher*)
{
	FCPPT_ASSERT_UNREACHABLE;
}
