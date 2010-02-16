#include "../world_hack.hpp"

sge::bullet::world_hack::world_hack(
	btDispatcher* const _a,
	btBroadphaseInterface* const _b,
	btConstraintSolver* const _c, 
	btCollisionConfiguration* _d)
:
	btDiscreteDynamicsWorld(
		_a,
		_b,
		_c,
		_d)
{
}

void
sge::bullet::world_hack::callback_hack()
{
	btScalar ts = 
		static_cast<btScalar>(0);
	saveKinematicState(
		ts);

	applyGravity();

	internalSingleStepSimulation(
		ts);
	synchronizeMotionStates();
}
