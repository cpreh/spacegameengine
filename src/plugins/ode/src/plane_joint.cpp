#include "../plane_joint.hpp"
#include "../world_wrapper.hpp"
#include "../body.hpp"

sge::ode::plane_joint::plane_joint(
	world_wrapper &_world,
	body &_body)
:
	id_(dJointCreatePlane2D(_world.id(),0))
{
	dJointAttach(id(),_body.id(),0);
}

dJointID &sge::ode::plane_joint::id()
{
	return id_;
}

dJointID const &sge::ode::plane_joint::id() const
{
	return id_;
}

sge::ode::plane_joint::~plane_joint()
{
	dJointDestroy(id());
}
