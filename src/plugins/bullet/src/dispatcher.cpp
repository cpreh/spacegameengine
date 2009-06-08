/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../dispatcher.hpp"
#include "../types.hpp"
#include <bullet/BulletCollision/CollisionDispatch/btCollisionConfiguration.h>
#include <bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>
#include <bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <boost/ref.hpp>

sge::bullet::dispatcher::dispatcher(
	btCollisionConfiguration &configuration,
	collision::callback_signal &collision)
:
	btCollisionDispatcher(&configuration),
	collision(collision)
{
	setNearCallback(&dispatcher::near_callback);
}

void sge::bullet::dispatcher::near_callback(
	btBroadphasePair &pair,
	btCollisionDispatcher &that, 
	btDispatcherInfo const &)
{
	dynamic_cast<dispatcher &>(that).collision(
		boost::ref(
			*static_cast<
				collision::satellite *
			>(
				static_cast<
					body_type*
				>(
					pair.m_pProxy0->m_clientObject
				)->getUserPointer()
			)
		),
		boost::ref(
			*static_cast<
				collision::satellite *
			>(
				static_cast<
					body_type*
				>(
					pair.m_pProxy1->m_clientObject
				)->getUserPointer()
			)
		)
	);
	
	// this calls the collisionDispatchers collision handling methods and 
	// activates the physics part of bullet (not needed here)
	//dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
}
