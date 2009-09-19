#include "../group.hpp"
#include "../body.hpp"
#include "../shapes/base.hpp"
#include <sge/math/null.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

sge::ode::group::group(
	group_id const _category)
:
	category_(
		_category),
	collides_(
		sge::math::null<group_id>()),
	dirty_(false)
{
}

void sge::ode::group::add(
	collision::shapes::base_ptr const _shape)
{
	dirty_ = 
		true;
	dynamic_cast<shapes::base &>(
		*_shape).add_to_group(
		*this);
}

void sge::ode::group::collides_with(
	collision::group_ptr const _group)
{
	group &other = 
		dynamic_cast<group &>(*_group);
	SGE_ASSERT_MESSAGE(!dirty_ && !other.dirty_,SGE_TEXT("Constraint violation: Tried to change a group which already has shapes in it"));
	collides_ |= other.category();
}

sge::ode::group_id sge::ode::group::category() const
{
	return category_;
}

sge::ode::group_id sge::ode::group::collides() const
{
	return collides_;
}
