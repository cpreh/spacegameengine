#ifndef SGE_ODE_JOINT_HPP_INCLUDED
#define SGE_ODE_JOINT_HPP_INCLUDED

#include <sge/noncopyable.hpp>

namespace sge
{
namespace ode
{
class joint
{
SGE_NONCOPYABLE(joint)
public:
	joint(
		dJointID);
	~joint();
	dJointID value() const;
private:
	dJointID value_;
};
}
}

#endif
