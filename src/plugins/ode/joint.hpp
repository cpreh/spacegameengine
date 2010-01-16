#ifndef SGE_ODE_JOINT_HPP_INCLUDED
#define SGE_ODE_JOINT_HPP_INCLUDED

#include "joint_fwd.hpp"
#include <ode/common.h>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace ode
{
class joint
{
	FCPPT_NONCOPYABLE(joint)
public:
	explicit joint(
		dJointID
	);
	~joint();

	dJointID
	value() const;
private:
	dJointID value_;
};
}
}

#endif
