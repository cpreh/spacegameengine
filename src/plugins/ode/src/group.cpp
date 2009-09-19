#include "../group.hpp"
#include "../body.hpp"
#include "../shapes/base.hpp"
#include <sge/math/null.hpp>

sge::ode::group::group(
	group_id _category)
:
	category_(
		_category),
	collides_(
		sge::math::null<group_id>())
{
}

void sge::ode::group::add(
	collision::shapes::base_ptr const _shape)
{
	dynamic_cast<shapes::base &>(
		*_shape).add_to_group(
		*this);
}

void sge::ode::group::collides_with(
	collision::group_ptr const _group)
{
	collides_ |= dynamic_cast<group &>(*_group).collides();
}

sge::ode::group_id sge::ode::group::category() const
{
	return category_;
}

sge::ode::group_id sge::ode::group::collides() const
{
	return collides_;
}