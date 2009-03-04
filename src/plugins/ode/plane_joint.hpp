#ifndef SGE_ODE_PLANE_JOINT_HPP_INCLUDED
#define SGE_ODE_PLANE_JOINT_HPP_INCLUDED

#include "world_fwd.hpp"
#include "body_fwd.hpp"
#include <boost/noncopyable.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class plane_joint : boost::noncopyable
{
public:
	plane_joint(
		world &,
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
