#include "../group.hpp"
#include "../body.hpp"
#include <fcppt/math/null.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>

sge::ode::group::group(
	group_id const _category)
:
	category_(
		_category),
	collides_(
		fcppt::math::null<group_id>()),
	dirty_(false)
{
}

void sge::ode::group::add(
	collision::body_ptr const _body)
{
	dirty_ =
		true;
	dynamic_cast<body &>(
		*_body).add_to_group(
		*this);
}

void sge::ode::group::collides_with(
	group const &other)
{
	FCPPT_ASSERT_MESSAGE(!dirty_ && !other.dirty_,FCPPT_TEXT("Constraint violation: Tried to change a group which already has shapes in it"));
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
