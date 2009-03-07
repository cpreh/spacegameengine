#ifndef SGE_ODE_PLANE_JOINT_HPP_INCLUDED
#define SGE_ODE_PLANE_JOINT_HPP_INCLUDED

#include "world_wrapper_fwd.hpp"
#include "body_fwd.hpp"
#include <sge/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class plane_joint
{
	SGE_NONCOPYABLE(plane_joint)
public:
	plane_joint(
		world_wrapper &,
		body &);
	dJointID &id();
	dJointID const &id() const;
	~plane_joint();
private:
	dJointID id_;
};
}
}

#endif
