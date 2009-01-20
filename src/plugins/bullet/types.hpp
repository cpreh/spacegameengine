#ifndef SGE_BULLET_TYPES_HPP_INCLUDED
#define SGE_BULLET_TYPES_HPP_INCLUDED

#include <memory>
#include <bullet/BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <bullet/BulletCollision/CollisionShapes/btCollisionShape.h>

namespace sge
{
namespace bullet
{
typedef btDynamicsWorld world_type;
typedef btRigidBody body_type;
typedef btCollisionShape shape_type;
typedef std::auto_ptr<shape_type> shape_ptr;
typedef btScalar unit;
typedef btVector3 point;

typedef btCollisionConfiguration configuration_type;
typedef btCollisionDispatcher dispatcher_type;
typedef btBroadphaseInterface broadphase_type;
typedef btConstraintSolver constraint_solver_type;
typedef btOverlapFilterCallback filter_callback_type;
}
}

#endif
