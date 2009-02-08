#include "../dispatcher.hpp"
#include "../types.hpp"
#include <bullet/BulletCollision/CollisionDispatch/btCollisionConfiguration.h>
#include <bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>
#include <bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h>

sge::bullet::dispatcher::dispatcher(
	btCollisionConfiguration &configuration,
	collision::callback_signal &collision)
	: btCollisionDispatcher(&configuration),
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
		*static_cast<collision::sattelite *>(
			static_cast<body_type*>(pair.m_pProxy0->m_clientObject)->getUserPointer()),
		*static_cast<collision::sattelite *>(
			static_cast<body_type*>(pair.m_pProxy1->m_clientObject)->getUserPointer()));
	
	// this calls the collisionDispatchers collision handling methods and 
	// activates the physics part of bullet (not needed here)
	//dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);
}
