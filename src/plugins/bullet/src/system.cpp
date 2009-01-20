#include "../system.hpp"
#include "../overlap_callback.hpp"
#include "../dispatcher.hpp"
#include "../objects/circle.hpp"
#include <sge/collision/sattelite.hpp>
#include <bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <boost/bind.hpp>

sge::bullet::system::system(collision::test_callback const &test)
	: collision::system(test),
		configuration(new btDefaultCollisionConfiguration()),
	  dispatcher(
			new sge::bullet::dispatcher(
				*configuration,
				callback_signal_)),
		broadphase(new btDbvtBroadphase()),
		constraint_solver(new btSequentialImpulseConstraintSolver()),
		overlap_callback_(
			new overlap_callback(
				boost::bind(&system::test,this,_1,_2))),
		world_(
			new btDiscreteDynamicsWorld(
				dispatcher.get(),
				broadphase.get(),
				constraint_solver.get(),
				configuration.get())),
		// mass, motion state*, shape*
		zero_body_(static_cast<unit>(0),0,0)
{
	world_->getPairCache()->setOverlapFilterCallback(overlap_callback_.get());
	// bullet sets a default gravity, so we have to reset this
	world_->setGravity(
		point(
			static_cast<unit>(0),
			static_cast<unit>(0),
			static_cast<unit>(0)));
}

sge::signals::connection const sge::bullet::system::register_callback(
	collision::callback const &fn)
{
	return callback_signal_.connect(fn);
}

sge::collision::object_ptr const sge::bullet::system::create_circle(
	collision::sattelite_ptr sat,
	collision::unit const radius)
{
	return collision::object_ptr(new objects::circle(*this,sat,radius));
}

void sge::bullet::system::update(time::funit const delta)
{
	/*
	world->stepSimulation(
		delta,
		static_cast<int>(
			static_cast<unit>(delta)/
				(static_cast<unit>(1)/static_cast<unit>(60)))+1);
				*/
	world_->stepSimulation(delta);
}

sge::bullet::world_type &sge::bullet::system::world()
{
	return *world_;
}

sge::bullet::body_type &sge::bullet::system::zero_body()
{
	return zero_body_;
}

sge::bullet::system::~system() {}
