#include "../world.hpp"
#include "../overlap_callback.hpp"
#include "../dispatcher.hpp"
#include "../objects/circle.hpp"
#include <sge/collision/satellite.hpp>
#include <bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <boost/spirit/home/phoenix/core/value.hpp>
#include <boost/bind.hpp>

sge::bullet::world::world()
:
	configuration(new btDefaultCollisionConfiguration()),
	dispatcher(
		new sge::bullet::dispatcher(
			*configuration,
			callback_signal_)),
	broadphase(new btDbvtBroadphase()),
	constraint_solver(new btSequentialImpulseConstraintSolver()),
	overlap_callback_(boost::phoenix::val(false)),
	world_(
		new btDiscreteDynamicsWorld(
			dispatcher.get(),
			broadphase.get(),
			constraint_solver.get(),
			configuration.get())),
	// mass, motion state*, shape*
	zero_body_(static_cast<unit>(0),0,0)
{
	world_->getPairCache()->setOverlapFilterCallback(&overlap_callback_);
	// bullet sets a default gravity, so we have to reset this
	world_->setGravity(
		point(
			static_cast<unit>(0),
			static_cast<unit>(0),
			static_cast<unit>(0)));
}

void sge::bullet::world::test_callback(
	collision::test_callback const &_test)
{
	overlap_callback_.reset(_test);
}

sge::signals::connection const sge::bullet::world::register_callback(
	collision::callback const &fn)
{
	return callback_signal_.connect(fn);
}

sge::collision::objects::circle_ptr const sge::bullet::world::create_circle(
	collision::satellite_ptr sat,
	collision::point const &center,
	collision::point const &speed,
	collision::unit const radius)
{
	return collision::objects::circle_ptr(
		new objects::circle(
			*this,
			sat,
			center,
			speed,
			radius));
}

void sge::bullet::world::update(
	collision::time_unit const delta)
{
	/*
	world_->stepSimulation(
		delta,
		static_cast<int>(
			static_cast<unit>(delta)/
				(static_cast<unit>(1)/static_cast<unit>(60)))+1);
				*/
	world_->stepSimulation(delta);
}

sge::bullet::world_type &sge::bullet::world::world_internal()
{
	return *world_;
}

sge::bullet::body_type &sge::bullet::world::zero_body()
{
	return zero_body_;
}

sge::bullet::world::~world() {}
