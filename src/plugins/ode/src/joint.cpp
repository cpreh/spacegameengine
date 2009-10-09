#include "../joint.hpp"

sge::ode::joint::joint(
	dJointID const _value)
:
	value_(
		_value)
{
}

sge::ode::joint::~joint()
{
	dJointDestroy(
		value_);
}

dJointID sge::ode::joint::value() const
{
	return value_;
}
